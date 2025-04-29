#include <iostream>
#include <cstring>
#include "MySet/MySet.h"

template<typename T>
void print_set(const MySet<T>& set) {
    std::cout << "{ ";
    for (size_t i = 0; i < set.size(); ++i)
        std::cout << set[i] << " ";
    std::cout << "}\n";
}

template<>
void print_set<char*>(const MySet<char*>& set) {
    std::cout << "{ ";
    for (size_t i = 0; i < set.size(); ++i) {
        if (set[i] != nullptr)
            std::cout << set[i] << " ";
        else
            std::cout << "(null) ";
    }
    std::cout << "}\n";
}

int main() {
    MySet<int> a, b;
    a.add_element(1);
    a.add_element(4);
    a.add_element(5);
    a.add_element(6);

    b.add_element(1);
    b.add_element(2);
    b.add_element(3);
    b.add_element(4);

    std::cout << "A: "; print_set(a);
    std::cout << "B: "; print_set(b);

    auto c = a + b;
    std::cout << "A + B: "; print_set(c);

    auto d = a * b;
    std::cout << "A * B: "; print_set(d);

    auto e = a - b;
    std::cout << "A - B: "; print_set(e);

    MySet<char*> sa, sb;

    sa.add_element(strdup("apple"));
    sa.add_element(strdup("orange"));
    sa.add_element(strdup("banana"));
    sa.add_element(strdup("apple"));

    sb.add_element(strdup("banana"));
    sb.add_element(strdup("kiwi"));
    sb.add_element(strdup("orange"));

    std::cout << "\n";

    std::cout << "SA: "; print_set(sa);
    std::cout << "SB: "; print_set(sb);

    auto sc = sa + sb;
    std::cout << "SA + SB: "; print_set(sc);

    auto sd = sa * sb;
    std::cout << "SA * SB: "; print_set(sd);

    auto se = sa - sb;
    std::cout << "SA - SB: "; print_set(se);

    for (size_t i = 0; i < sa.size(); ++i) free(sa[i]);
    for (size_t i = 0; i < sb.size(); ++i) free(sb[i]);
    for (size_t i = 0; i < sc.size(); ++i) free(sc[i]);
    for (size_t i = 0; i < sd.size(); ++i) free(sd[i]);
    for (size_t i = 0; i < se.size(); ++i) free(se[i]);

    return 0;
}
