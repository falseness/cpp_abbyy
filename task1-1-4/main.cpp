#include <iostream>
#include <ranges>
#include <algorithm>


int main() {
    // https://godbolt.org/z/PfTj76bz4
    // первая часть
    for (const auto& value: std::ranges::istream_view<int>(std::cin)) {
        if (value == -1) {
            break;
        }
        std::cout << value << ' ';
    }
    std::cout << '\n';
    // вторая часть
    auto input = std::ranges::istream_view<int>(std::cin) |
                 std::ranges::views::take_while([](auto&& x) {return x != -1;});

    std::ranges::copy(
            input,
            std::ostream_iterator<float>{std::cout, " "}
    );
}
