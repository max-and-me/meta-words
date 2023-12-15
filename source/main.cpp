// Copyright Max & Me 2023

#include "mam/meta_words/runner.h"

using namespace mam::meta_words;

int main()
{
    // whisper.cpp executable
    const PathType executable =
        "/mnt/veracrypt2/Developer/github/whisper_test/build/bin/"
        "main";
    //  The whisper.cpp library takes the audio file and writes the result of
    //  its analysis into a CSV file. The file is named like the audio file and
    //  by prepending ".csv" e.g. my_speech.wav -> my_speech.wav.csv
    const Options options         = {"-ocsv"};
    const OneValArgs one_val_args = {
        // model file resp. binary
        {"-m", "/mnt/veracrypt2/Developer/github/whisper_test/whisper.cpp/"
               "models/ggml-base.en.bin"},
        // audio file to analyse
        {"-f", "/mnt/veracrypt2/Developer/github/"
               "whisper_test/whisper.cpp/samples/jfk.wav"},
        // maximum segment length in characters: "1" mains one word
        {"-ml", "1"}};

    Command cmd{executable, options, one_val_args};

    FnProgress fn_progress = [](ProgressValue val) {
        // https://github.com/openai/whisper/discussions/850
        // TODO: Does not work ...yet!
        double tmp = val;
    };

    const auto meta_words = run(cmd, fn_progress);

    return 0;
}