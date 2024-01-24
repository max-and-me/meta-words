//--------------------------------------------------------------------
// Copyright Max & Me 2024
//--------------------------------------------------------------------


#include <string>
#include <vector>

namespace mam::meta_words {

//--------------------------------------------------------------------
struct MetaWord
{
    using Word = std::string;

    double begin    = 0.;
    double duration = 0.;
    Word word;
};

using MetaWords = std::vector<MetaWord>;

//--------------------------------------------------------------------
} // namespace mam::meta_words
