// Copyright Max & Me 2023

#include "meta_word.h"
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace mam::meta_words {

//--------------------------------------------------------------------
using StringType    = std::string;
using PathType      = const StringType;
using Options       = const std::vector<StringType>;
using OneValArgs    = const std::unordered_map<StringType, StringType>;
using ProgressValue = const double;
using FnProgress    = const std::function<void(ProgressValue)>;

struct Command
{
    PathType executable;
    Options options;
    OneValArgs one_value_args;
};

const MetaWords run(const Command& cmd, FnProgress& fn_progress);

//--------------------------------------------------------------------
} // namespace mam::meta_words
