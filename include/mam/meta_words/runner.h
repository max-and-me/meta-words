//--------------------------------------------------------------------
// Copyright Max & Me 2024
//--------------------------------------------------------------------

#pragma once

#include "meta_word.h"
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include "tl/expected.hpp"

namespace mam::meta_words {

//--------------------------------------------------------------------
using StringType    = std::string;
using PathType      = const StringType;
using Options       = const std::vector<StringType>;
using OneValArgs    = const std::unordered_map<StringType, StringType>;
using ProgressValue = const double;
using FuncProgress  = const std::function<void(ProgressValue)>;
using FuncCancel    = const std::function<bool()>;
using ExpectedMetaWords = tl::expected<MetaWords, int>;

struct Command
{
    PathType executable;
    Options options;
    OneValArgs one_value_args;
};

const ExpectedMetaWords
run(const Command& cmd, FuncProgress&& progress_func, FuncCancel&& cancel_func);

//--------------------------------------------------------------------
} // namespace mam::meta_words
