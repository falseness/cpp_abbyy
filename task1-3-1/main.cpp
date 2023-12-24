#include <iostream>
#include <vector>
#include <string>
#include <concepts>

template <typename T>
concept ToStringable = std::is_arithmetic_v<T> && !std::is_same_v<T, bool> &&
requires (T a) {std::to_string(a);};

template <ToStringable T1, ToStringable T2>
std::string concat(T1 t1, T2 t2) {
return std::to_string(t1) + std::to_string(t2);
}

template <typename T1, typename T2>
concept CanBeConcatted = requires (T1 t1, T2 t2) {concat(t1, t2);};

int main() {
    // Оно же: https://godbolt.org/z/M3xKh9c5K
    static_assert(CanBeConcatted<int, float>);
    static_assert(!CanBeConcatted<float, bool>);
    static_assert(!CanBeConcatted<char*, double>);
    // считаем ли мы char - целым числом? я - да.
    static_assert(CanBeConcatted<char, short>);
}
