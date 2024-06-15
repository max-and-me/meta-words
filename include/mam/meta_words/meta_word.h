//--------------------------------------------------------------------
// Copyright Max & Me 2024
//--------------------------------------------------------------------

#pragma once

#include <string>
#include <vector>

namespace mam::meta_words {

//--------------------------------------------------------------------
struct MetaWord
{
    using StringType = std::string;

    double begin    = 0.;
    double duration = 0.;
    StringType value;
};

using MetaWords = std::vector<MetaWord>;

//--------------------------------------------------------------------
} // namespace mam::meta_words
