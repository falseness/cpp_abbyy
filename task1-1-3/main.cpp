#include <iostream>
#include <vector>
#include <ranges>
#include <tuple>

template < typename InputIter , typename OutputIter >
void myCopy ( InputIter begin , InputIter end , OutputIter target ) {
    for ( auto iter { begin }; iter != end ; ++ iter , ++ target ) { * target = * iter ; }
}

struct Person {
    std::string name;
    std::string surname;
};

std::ostream& operator<<(std::ostream& output, const Person& person) {
    output << person.name << ' ' << person.surname;
    return output;
}


int main() {
    // https://godbolt.org/z/K6def8x8c
    std::vector<std::pair<Person, size_t>> persons;
    persons.emplace_back(Person{"A", "Ba"}, 1);
    persons.emplace_back(Person{"Ca", "Ba"}, 12);
    persons.emplace_back(Person{"Da", "Ba"}, 42);
    persons.emplace_back(Person{"Pa", "Pa"}, 88);
    persons.emplace_back(Person{"X", "Yz"}, 3);

    auto projected = std::views::keys(persons) | std::ranges::views::take(4);
    myCopy(projected.begin(), projected.end(), std::ostream_iterator<Person>(std::cout, "\n"));
    auto surnames = projected | std::ranges::views::transform([](auto&& x) {return x.surname;});
    myCopy(surnames.begin(), surnames.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}
