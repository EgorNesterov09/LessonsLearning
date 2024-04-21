#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <variant>
#include <unordered_map>
#include <cassert>

// (1 + 2) * 3 / 4 + 5 * (6 - 7)

// 1. Токенизация
// 2. Парсер (построение дерева разбора выражения)

// +, -, *, /, %

struct OpeningBracket {};

struct ClosingBracket {};

struct Number {
  int value;
};

struct UnknownToken {
  std::string value;
};

struct MinToken {};

struct AbsToken {};

struct MaxToken {};

struct Plus {};

struct Minus {};

struct Multiply {};

struct Modulo {};

struct Divide {};

struct SqrtToken {};

using Token = std::variant<OpeningBracket, ClosingBracket, Number, UnknownToken, MinToken, AbsToken, MaxToken, Plus, Minus, Multiply, Modulo, Divide, SqrtToken>;

// 1234

const std::unordered_map<char, Token> kSymbol2Token{
    {'+', Plus{}}, {'-', Minus{}}, {'*', Multiply{}}, {'/', Divide{}}, {'%', Modulo{}}, {'(', OpeningBracket{}}, {')', ClosingBracket{}}
};

const std::unordered_map<std::string, Token> String2Token{
    {"min", MinToken{}}, {"max", MaxToken{}}, {"abs", AbsToken{}}, {"sqrt", SqrtToken{}}
};

int ToDigit(unsigned char symbol) {
  return symbol - '0';
}

Number ParseNumber(const std::string& input, size_t& pos) {
  int value = 0;
  auto symbol = static_cast<unsigned char>(input[pos]);
  while (std::isdigit(symbol)) {
    value = value * 10 + ToDigit(symbol);
    if (pos == input.size() - 1) {
      break;
    }
    symbol = static_cast<unsigned char>(input[++pos]);
  }
  return Number{value};
}

Token ParseName(const std::string& input, size_t& pos) { //min, max, abs, sqrt;
    std::string name;
    auto symbol = static_cast<unsigned char>(input[pos]);
    while (std::isdigit(symbol)) {
        name += symbol;
        if (pos == input.size() - 1) {
            break;
        }
        symbol = static_cast<unsigned char>(input[++pos]);
    }
    if (auto it = String2Token.find(name); it != String2Token.end()) {
        return it->second;
    }
    return UnknownToken(name);     
}

std::vector<Token> Tokenize(const std::string& input) {
  std::vector<Token> tokens;
  const size_t size = input.size();
  size_t pos = 0;
  while (pos < size) {
    const auto symbol = static_cast<unsigned char>(input[pos]);
    if (std::isspace(symbol)) {
      ++pos;
    } else if (std::isdigit(symbol)) {
      tokens.emplace_back(ParseNumber(input, pos));
    } else if (auto it = kSymbol2Token.find(symbol); it != kSymbol2Token.end()) {
      tokens.emplace_back(it->second);
    }
    else if (std::isalpha(symbol)) {
        tokens.emplace_back(ParseName(input, pos));
    }
  }
  return tokens;
}

int main() {
    //(1 + 2) + 3 * sqr(4) ->[(, 1, +, 2, ), +, 3, *, SqrToken, (, 4, )]
    std::vector<Token> tokens = Tokenize("(1 + 2) ");
    std::vector<Token> expected_tokens = { OpeningBracket{}, Number{1}, Plus{}, Number{2}, ClosingBracket{} };
    assert(tokens == expected_tokens);
    std::cout << "Comlete" << std::endl;
}
