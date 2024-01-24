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
        std::cout << word.word;
    }
}

//-----------------------------------------------------------------------------
void run_sync(Command& cmd)
{
    std::cout << "Run sync..." << '\n';

    FnProgress fn_progress = [](ProgressValue val) { ProgressValue tmp = val; };

    print_result(run(cmd, fn_progress));
}

//-----------------------------------------------------------------------------
void run_async(Command& cmd)
{
    std::cout << "Run async..." << '\n';

    std::future<MetaWords> future_handle = std::async([&]() {
        FnProgress fn_progress = [](ProgressValue val) { ProgressValue tmp = val; };

        return run(cmd, fn_progress);
    });

    // Our idle loop...
    while (true)
    {
        std::cout << "Idle timer..." << '\n';
        // '0': ask for the future state immediately. There is no waiting!
        if (future_handle.wait_for(std::chrono::seconds(0)) ==
            std::future_status::ready)
            break;

        // Simulate the ilde timer
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    print_result(future_handle.get());
}

//-----------------------------------------------------------------------------
int main()
{
    // whisper.cpp executable
    const PathType executable =
        "/Users/max/Documents/Code/vst-gpt/build_whisper/bin/"
        "main";
    //  The whisper.cpp library takes the audio file and writes the result
    //  of its analysis into a CSV file. The file is named like the audio
    //  file and by prepending ".csv" e.g. my_speech.wav ->
    //  my_speech.wav.csv
    const Options options         = {"-ocsv"};
    const OneValArgs one_val_args = {
        // model file resp. binary
        {"-m", "/Users/max/Documents/Code/vst-gpt/whisper.cpp/models/ggml-base.en.bin"},
        // audio file to analyse
        {"-f", "/Users/max/Desktop/max.wav"},
        // maximum segment length in characters: "1" mains one word
        {"-ml", "1"}};

    Command cmd{executable, options, one_val_args};

    run_sync(cmd);
    run_async(cmd);

    return 0;
}
