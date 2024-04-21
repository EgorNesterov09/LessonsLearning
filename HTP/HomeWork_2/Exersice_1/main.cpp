#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <variant>
#include <unordered_map>
#include <cassert>

// (1 + 2) * 3 / 4 + 5 * (6 - 7)

// 1. Токенизация

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

struct Comma {};

struct Plus {};

struct Minus {};

struct Multiply {};

struct Modulo {};

struct Divide {};

struct SqrtToken {};

using TokenBase = std::variant<OpeningBracket, ClosingBracket, Number, UnknownToken, MinToken, 
                 AbsToken, MaxToken, Plus, Minus, Multiply, Modulo, Divide, SqrtToken, Comma>;

struct Token : TokenBase {
    using TokenBase::TokenBase;

    template <typename T>
    [[nodiscard]] bool Is() const {
        return std::holds_alternative<T>(*this);
    }

    template <typename T>
    [[nodiscard]] const T& As() const {
        return std::get<T>(*this);
    }

    template <typename T>
    [[nodiscard]] const T* TryAs() const {
        return std::get_if<T>(this);
    }
};

const std::unordered_map<char, Token> kSymbol2Token{
    {'+', Plus{}}, {'-', Minus{}}, {'*', Multiply{}}, {'/', Divide{}}, {'%', Modulo{}}, {'(', OpeningBracket{}}, 
    {')', ClosingBracket{}}, {',', Comma{}} };

const std::unordered_map<std::string, Token> String2Token{
    {"min", MinToken{}}, {"max", MaxToken{}}, {"abs", AbsToken{}}, {"sqrt", SqrtToken{}} };

bool operator==(const Token& lhs, const Token& rhs) {

    if (lhs.index() != rhs.index()) {
        return false;
    }
    if (lhs.Is<Number>()) {
        return lhs.As<Number>().value == rhs.As<Number>().value;
    }
    if (lhs.Is<Number>()) {
        return lhs.As<UnknownToken>().value == rhs.As<UnknownToken>().value;
    }
    return true;
}

bool operator!=(const Token& lhs, const Token& rhs) {
    return !(lhs == rhs);
}

int ToDigit(unsigned char symbol) {
  return symbol - '0';
}

Number ParseNumber(const std::string& input, size_t& pos) {
  int value = 0;
  auto symbol = static_cast<unsigned char>(input[pos]);
  while (std::isdigit(symbol)) {
    value = value * 10 + ToDigit(symbol);
    if (pos == input.size() - 1) {
        ++pos;
        break;
    }
    symbol = static_cast<unsigned char>(input[++pos]);
  }
  return Number{value};
}

Token ParseName(const std::string& input, size_t& pos) { //min, max, abs, sqrt;
    std::string name;
    auto symbol = static_cast<unsigned char>(input[pos]);
    while (!std::isspace(symbol) && symbol != '(') {
        name += symbol;
        if (pos == input.size() - 1) {
            ++pos;
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
        ++pos;
    } else {
        tokens.emplace_back(ParseName(input, pos));
    }
  }
  return tokens;
}

int main() {
    //min(4, 1 + 16 / 2) + (1 + 2) + 3 * sqr(444) + #7ds&y7 -> 
    // -> [min, (, 4, ',', 1, +, 16, *, 2, ), +, (, 1, +, 2, ), +, 3, *, SqrToken, (, 4, ), +, #7ds&y7]
    std::string query = "   min(4, 1 + 16 / 2 ) +(11   + 549832 )    + 3 *   sqrt   (444   ) +   #7ds&y7 ";
    std::vector<Token> tokens = Tokenize(query);
    std::vector<Token> expected_tokens = {  MinToken{}, OpeningBracket{}, Number{4}, Comma{}, Number{1}, Plus{}, Number{16}, Divide{},
                                            Number{2}, ClosingBracket{}, Plus{}, OpeningBracket{},  Number{11}, Plus{}, Number{549832}, 
                                            ClosingBracket{}, Plus{}, Number{3}, Multiply{}, SqrtToken{}, OpeningBracket{}, Number{444}, 
                                            ClosingBracket{}, Plus{}, UnknownToken {"#7ds&y7"} };
    assert(tokens == expected_tokens);
    std::cout << "Comlete" << std::endl;
}
