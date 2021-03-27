#ifndef SBX_TOKENIZE_HPP
#define SBX_TOKENIZE_HPP

#include <queue>
#include <sstream>
#include <string>

namespace Sandbox
{

// split up a sequence of characters into a sequence of tokens
static std::queue<std::string> Tokenize(const std::string sequence, char delimiter)
{
    std::stringstream sstr(sequence);
    std::queue<std::string> tokens;

    while (sstr.good())
    {
        std::string token;
        std::getline(sstr, token, delimiter);
        tokens.push(token);
    }

    return tokens;
}

} // namespace Sandbox

#endif
