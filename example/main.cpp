// SPDX-License-Identifier: GPL-3.0-only
#include <localid.hpp>
#include <unordered_set>

int main() {
    // string based initialization
    localid id1("36NGCUN");
    std::cout << "id1: " << id1 << '\n';

    // random id default initialization
    localid id2;
    std::cout << "id2: " << id2 << '\n';

    // integer based initialization (with same value as id1)
    localid id3(3446158198u);
    std::cout << "id3: " << id3 << '\n';

    // usage in unordered_set or unordered_map
    std::unordered_set< localid<> > uost{ id1, id2, id3 };

    std::cout << "Unordered Set Size: " << uost.size() << '\n'; // size = 2 as id1 = id3

    // comparison operators
    std::cout << std::boolalpha << "id1 > id2 : " << (id1 > id2) << '\n';
    std::cout << std::boolalpha << "id1 = id3 : " << (id1 == id3) << '\n';

    // static cast to fundamental ints
    std::cout << "unsigned cast id3: " << static_cast<unsigned>(id3) << '\n';

    // invalid initialization (character 'O' is not allowed)
    localid id4("WOW6969");
    std::cout << "is valid id4: " << std::boolalpha << id4.is_valid() << '\n';
}