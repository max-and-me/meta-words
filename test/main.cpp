//--------------------------------------------------------------------
// Copyright Max & Me 2024
//--------------------------------------------------------------------

#include "mam/meta_words/runner.h"
#include <future>
#include <iostream>
#include <thread>

using namespace mam::meta_words;

//-----------------------------------------------------------------------------
void print_result(const MetaWords& meta_words)
{
    for (auto& word : meta_words)
    {
        std::cout << word.value;
    }
}

//-----------------------------------------------------------------------------
void run_sync(Command& cmd)
{
    std::cout << "Run sync..." << '\n';

    FuncProgress progress_func = [](ProgressValue val) {
        ProgressValue tmp = val;
    };
    FuncCancel cancel_func = []() { return false; };

    print_result(run(cmd, std::move(progress_func), std::move(cancel_func)));
}

//-----------------------------------------------------------------------------
void run_async(Command& cmd)
{
    std::cout << "Run async..." << '\n';

    std::atomic_bool is_cancel = false;

    std::future<MetaWords> future_handle = std::async([&]() {
        FuncProgress progress_func = [](ProgressValue val) {
            ProgressValue tmp = val;
        };

        FuncCancel cancel_func = [&]() { // TODO
            return is_cancel.load();
        };

        return run(cmd, std::move(progress_func), std::move(cancel_func));
    });

    // Our idle loop...
    auto counter = 0;
    while (true)
    {
        std::cout << "Idle timer..." << '\n';
        // '0': ask for the future state immediately. There is no waiting!
        if (future_handle.wait_for(std::chrono::seconds(0)) ==
            std::future_status::ready)
            break;

        if (counter > 20)
            is_cancel = true;

        // Simulate the ilde timer
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        counter++;
    }

    print_result(future_handle.get());
}

//-----------------------------------------------------------------------------
int main()
{
    // whisper.cpp executable
    const PathType executable = MAM_WHISPER_CPP_EXECUTABLE;
    //  The whisper.cpp library takes the audio file and writes the result
    //  of its analysis into a CSV file. The file is named like the audio
    //  file and by prepending ".csv" e.g. my_speech.wav ->
    //  my_speech.wav.csv
    const Options options         = {"-ocsv"};
    const OneValArgs one_val_args = {
        // model file resp. binary
        {"-m", MAM_WHISPER_CPP_MODEL_DOWNLOAD_DIR "/ggml-medium.bin"},
        // audio file to analyse
        {"-f", MAM_WHISPER_CPP_AUDIO_SAMPLES_DIR "/jfk.wav"},
        // maximum segment length in characters: "1" mains one word
        {"-ml", "1"}};

    Command cmd{executable, options, one_val_args};

    // run_sync(cmd);
    run_async(cmd);

    return 0;
}
