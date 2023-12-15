// Copyright Max & Me 2023

#include "mam/meta_words/runner.h"
#include "csv.h"
#include "process.hpp"
#include <string>

namespace mam::meta_words {

//--------------------------------------------------------------------
StringType build_command(const Command& cmd)
{
    StringType command = cmd.executable;
    for (const auto& opt : cmd.options)
        command += " " + opt;

    for (const auto& arg : cmd.one_value_args)
        command += " " + arg.first + " " + arg.second;

    return command;
}

//--------------------------------------------------------------------
bool run_whisper_cpp(const Command& cmd, FnProgress& fn_progress)
{
    // callbacks for stdout an stderr
    StringType output;
    StringType error;

    auto read_stdout = [&output, &fn_progress](const char* bytes, size_t n) {
        // TODO: not working yet :-/
        // fn_progress(0.);
        output += StringType(bytes, n);
    };

    auto read_stderr = [&error](const char* bytes, size_t n) {
        error += StringType(bytes, n);
    };

    // Working directory is not needed here actually (?)
    const char* kPath = "/";

#ifndef _WIN32
    TinyProcessLib::Process process(build_command(cmd), kPath, read_stdout,
                                    read_stderr, true);

    return process.get_exit_status() == 0;

#endif

    return false;
}

//--------------------------------------------------------------------
const MetaWords parse_csv_file(PathType csv_file)
{
    MetaWords meta_words;

    io::CSVReader<3, io::trim_chars<' ', '\t'>,
                  io::double_quote_escape<',', '"'>>
        in(csv_file.c_str());
    in.read_header(io::ignore_extra_column, "start", "end", "text");
    double start = 0.;
    double end   = 0.;
    StringType text;
    while (in.read_row(start, end, text))
    {
        meta_words.push_back({start, end - start, text});
    }

    return meta_words;
}

//--------------------------------------------------------------------
PathType build_csv_file_path(OneValArgs& args)
{
    const auto citer = args.find("-f");
    if (citer == args.end())
        return {};

    const PathType& path = (*citer).second + ".csv";
    return path;
}

//--------------------------------------------------------------------
//  Public Interface
//--------------------------------------------------------------------
const MetaWords run(const Command& cmd, FnProgress& fn_progress)
{
    fn_progress(0.);

    if (!run_whisper_cpp(cmd, fn_progress))
        return {};

    const PathType& csv_file_path = build_csv_file_path(cmd.one_value_args);
    const MetaWords meta_words    = parse_csv_file(csv_file_path);

    fn_progress(1.);

    return meta_words;
}

//--------------------------------------------------------------------

} // namespace mam::meta_words