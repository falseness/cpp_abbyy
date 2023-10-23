#include <iostream>
#include <vector>
#include <ranges>
#include <tuple>

void printRange(std::string_view message, auto& range) {
    std::cout << message << '\n';
    for (const auto& value : range)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

struct Person {
    std::string name;
    std::string surname;
};

template < typename InputIter >
auto sum( InputIter begin , InputIter end )
{
    auto sum { * begin };
    for ( auto iter { ++ begin }; iter != end ; ++ iter ) {
        sum += * iter ;
    }
    return sum;
}

int main() {
    // https://godbolt.org/z/K1K634qdv
    std::vector<std::pair<Person, size_t>> persons;
    persons.emplace_back(Person{"A", "Ba"}, 1);
    persons.emplace_back(Person{"Ca", "Ba"}, 12);
    persons.emplace_back(Person{"Da", "Ba"}, 42);

    auto projected = std::views::values(persons);
    printRange("projected", projected);
    auto filtered = std::ranges::views::filter(projected, [](size_t age) {return age >= 12 && age <= 65; });
    printRange("filtered", filtered);
    std::cout << "sum\n";
    // не было сказано, считать в double или в int'ах
    std::cout << sum(filtered.begin(), filtered.end()) / std::distance(filtered.begin(), filtered.end());
}
