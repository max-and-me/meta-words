//--------------------------------------------------------------------
// Copyright Max & Me 2024
//--------------------------------------------------------------------

#include "mam/meta_words/runner.h"
#if _WIN32
#include "mam/utf_8_everywhere/convert.h"
#endif
#include "csv.h"
#include "process.hpp"
#include <filesystem>
#include <string>
#include <thread>

namespace mam::meta_words {

//------------------------------------------------------------------------
#if defined(WIN32)
constexpr auto QUOTE = "\"";
#else
constexpr auto QUOTE = "'";
#endif

//------------------------------------------------------------------------
auto put_in_quotes(const StringType& in) -> StringType
{
    return QUOTE + in + QUOTE;
}

//--------------------------------------------------------------------
StringType build_command(const Command& cmd)
{
    StringType command = put_in_quotes(cmd.executable);
    for (const auto& opt : cmd.options)
        command += " " + opt;

    for (const auto& arg : cmd.one_value_args)
        command += " " + arg.first + " " + put_in_quotes(arg.second);

    return command;
}

//--------------------------------------------------------------------
StringType get_whisper_bin_path(const StringType& executable)
{
    std::string string = executable;
    std::vector<std::string> tokens;
    std::string delimiter = "/";
    std::string token;
    size_t pos = 0;
    while ((pos = string.find(delimiter)) != std::string::npos)
    {
        token = string.substr(0, pos);
        tokens.push_back(token);
        string.erase(0, pos + delimiter.length());
    }
    string.clear();

    for (const auto& str : tokens)
        if (str.empty() == false)
            string = string + "/" + str;

    return string;
}

//--------------------------------------------------------------------
bool run_whisper_cpp(const Command& cmd,
                     FuncProgress&& progress_func,
                     FuncCancel&& cancel_func)
{
    // callbacks for stdout an stderr
    StringType output;
    StringType error;

    auto read_stdout = [&output, &progress_func](const char* bytes, size_t n) {
        // TODO: not working yet :-/
        // progress_func(0.);
        output += StringType(bytes, n);
    };

    auto read_stderr = [&error](const char* bytes, size_t n) {
        error += StringType(bytes, n);
    };

#ifndef _WIN32
    std::string binary_path = get_whisper_bin_path(cmd.executable);
    TinyProcessLib::Process process(build_command(cmd), binary_path.c_str(),
                                    read_stdout, read_stderr, true);
#else
    // Working directory is not needed here actually (?)
    const auto kPath    = L"/";
    const auto command  = build_command(cmd);
    const auto wcommand = utf_8_everywhere::convert(command);
    TinyProcessLib::Process process(wcommand, kPath, read_stdout, read_stderr,
                                    true);
#endif
    progress_func(0.);

    while (true)
    {
        int exit_status;
        if (process.try_get_exit_status(exit_status))
        {
            return exit_status == 0;
        }

        if (cancel_func())
        {
            process.kill();
            break;
        }

        // Wait some time before going on
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    progress_func(1.);

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
bool remove_if_exists(PathType file)
{
    // TODO: Add proper error handling here!
    std::error_code error_code;
    if (!std::filesystem::remove(file, error_code))
        return false;

    return true;
}

//--------------------------------------------------------------------
//  Public Interface
//--------------------------------------------------------------------
const MetaWords
run(const Command& cmd, FuncProgress&& progress_func, FuncCancel&& cancel_func)
{
    // whisper.cpp writes the result into a csv file. Remove this first if it
    // exists already.
    const PathType& csv_file_path = build_csv_file_path(cmd.one_value_args);
    remove_if_exists(csv_file_path);

    if (!run_whisper_cpp(cmd, std::move(progress_func), std::move(cancel_func)))
        return {};

    const MetaWords meta_words = parse_csv_file(csv_file_path);

    return meta_words;
}

//--------------------------------------------------------------------

} // namespace mam::meta_words
