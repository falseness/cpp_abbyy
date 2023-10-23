#include <iostream>
#include <ranges>


void printRange(std::string_view message, auto& range) {
    std::cout << message << '\n';
    for (const auto& value : range)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

int main() {
    // https://godbolt.org/z/1s1TaWhME
    // не было указано, включительно или нет
    auto result = std::views::iota(10, 100) |
                  std::views::transform([](auto&& x) {return x * x;}) |
                  std::views::filter([](auto&& x) {return x % 5 != 0;}) |
                  std::views::transform([](auto&& x) {return std::to_string(x);});
    printRange("result", result);
}
