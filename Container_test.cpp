/// @file pa14.cpp
/// @author Sujin Lee
/// @date 2022-03-10
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
/// @brief Catch2 teamplate Unit tests for the dynamic Container
/// 2022-03-02: Created by Kevin
/// 2022-03-03: Sujin copied from shared directory
/// 2022-03-04: modified deprecated function uses
/// 2022-03-10: add templaete case for erase(try&catch),
///             test cases for at[] operator

#define CATCH_CONFIG_MAIN
#if defined __linux__
#include <catch.hpp>
#elif defined __MACH__
#include </opt/local/include/catch2/catch.hpp>
#else
#include "catch.hpp"
#endif

#include <algorithm>
#include <initializer_list>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdexcept>
#include <utility>

#include "Container.hpp"

TEMPLATE_TEST_CASE("Container(size_type)", "", char, int, double) {
    Container<TestType> box1{};

    CHECK(box1.size() == 0);
    CHECK(box1.empty() == true);

    Container<TestType> box2(42);

    CHECK(box2.size() == 0);
    CHECK(box2.empty() == true);
}

TEMPLATE_TEST_CASE("Container(const Container&)", "", char, int, double) {
    const Container<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72 };
    const Container<TestType> box1(REF);

    CHECK(box1.size() == REF.size());
    CHECK(std::equal(box1.begin(), box1.end(), REF.begin(), REF.end()) == true);
}

/*
TEMPLATE_TEST_CASE("Container(Container&&)", "", char, int, double) {
    struct ContainerNoCopy : public Container<TestType> {
        using Container<TestType>::Container;
        ContainerNoCopy(const ContainerNoCopy&) = delete;
        ContainerNoCopy& operator=(const ContainerNoCopy&) = delete;
        ContainerNoCopy(ContainerNoCopy&&) = default;
        ContainerNoCopy& operator=(ContainerNoCopy&&) = default;
    };

    const ContainerNoCopy REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    ContainerNoCopy box1(std::move(ContainerNoCopy{ 65, 66, 67, 68, 69, 70, 71, 72 }));

    CHECK(box1.size() == REF.size());
    CHECK(std::equal(box1.begin(), box1.end(), REF.begin(), REF.end()) == true);
}
*/
TEMPLATE_TEST_CASE("Container(initializer_list)", "", char, int, double) {
    const std::initializer_list<TestType> INIT {
        65, 66, 67, 68, 69, 70, 71, 72
    };

    const Container<TestType> box1 { INIT };

    REQUIRE(box1.size() == INIT.size());
    REQUIRE(std::equal(box1.begin(), box1.end(), INIT.begin(), INIT.end()) == true);
}

TEST_CASE("~Container()") {}

TEMPLATE_TEST_CASE("Container& operator=(const Container&)", "", char, int, double) {
    const Container<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    Container<TestType> box1{};
    box1 = REF;

    CHECK(box1.size() == REF.size());
    CHECK(box1.begin() != REF.begin());
    CHECK(std::equal(box1.begin(), box1.end(), REF.begin(), REF.end()) == true);

}

/// template test case for move assignment operator
TEMPLATE_TEST_CASE("Container& operator=(Container&&)", "", char, int, double) {
    const Container<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    Container<TestType> box1{};
    box1 = REF;

    CHECK(box1.size() == REF.size());
    CHECK(box1.begin() != REF.begin());
    CHECK(std::equal(box1.begin(), box1.end(), REF.begin(), REF.end()) == true);

    // check self-assignment
    box1 = box1;

    CHECK(box1.size() == REF.size());
    CHECK(box1.begin() != REF.begin());
    CHECK(std::equal(box1.begin(), box1.end(), REF.begin(), REF.end()) == true);
}

TEMPLATE_TEST_CASE("Container& operator+=(const Container&)", "", char, int, double) {
    const Container<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    Container<TestType> box1{};

    box1 += REF;
    box1 += box1 += box1;

    REQUIRE(box1.size() == REF.size() * 4);

    CHECK(std::equal(box1.begin(), box1.begin() + REF.size(),
                     REF.begin(), REF.end()) == true);
    CHECK(std::equal(box1.begin() + REF.size(), box1.begin() + REF.size() * 2,
                     REF.begin(), REF.end()) == true);
    CHECK(std::equal(box1.begin() + REF.size() * 2, box1.begin() + REF.size() * 3,
                     REF.begin(), REF.end()) == true);
    CHECK(std::equal(box1.begin() + REF.size() * 3, box1.end(),
                     REF.begin(), REF.end()) == true);
}

TEMPLATE_TEST_CASE("empty()", "", char, int, double) {
    Container<TestType> box1{};

    CHECK(box1.empty() == true);

    box1.push_back(42);
    CHECK(box1.empty() == false);

    box1.clear();
    CHECK(box1.empty() == true);
}

TEMPLATE_TEST_CASE("size()", "", char, int, double) {
    const Container<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    Container<TestType> box1{};
    Container<TestType> box2{ REF };

    CHECK(box1.size() == 0);
    CHECK(box2.size() == REF.size());

    box2.clear();
    CHECK(box2.size() == 0);
}

TEST_CASE("begin()") {}
TEST_CASE("begin() const") {}
TEST_CASE("end()") {}
TEST_CASE("end() const") {}

TEMPLATE_TEST_CASE("push_back()", "", char, int, double) {
    const Container<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72, 0 };
    const auto SIZE = REF.size();

    Container<TestType> box1{};
    const auto original = box1.begin();

    for (auto value : REF) {
        box1.push_back(value);
    }

    for (auto value : REF) {
        box1.push_back(value);
    }

    CHECK(box1.size() == (SIZE * 2));
    CHECK(box1.begin() != original);
    CHECK(std::equal(box1.begin(), box1.begin() + SIZE, REF.begin(), REF.end()) == true);
    CHECK(std::equal(box1.begin() + SIZE, box1.end(), REF.begin(), REF.end()) == true);
}

TEMPLATE_TEST_CASE("erase()", "", char, int, double) {
    Container<TestType> box1 { 65, 66, 67, 68 };

    // delete last element
    box1.erase(box1.end() - 1);
    CHECK(box1.size() == 3);
    CHECK(std::find(box1.begin(), box1.end(), 68) == box1.end());

    // delete middle element
    box1.erase(box1.begin() + box1.size() / 2);
    CHECK(box1.size() == 2);
    CHECK(std::find(box1.begin(), box1.end(), 66) == box1.end());

    // delete front element
    box1.erase(box1.begin());
    CHECK(box1.size() == 1);
    CHECK(std::find(box1.begin(), box1.end(), 65) == box1.end());

    // delete final element, leaving empty container
    CHECK(*box1.begin() == 67);
    box1.erase(box1.begin());
    CHECK(box1.empty() == true);
    CHECK(box1.size() == 0);
}

/// test for rease function to check try-catch block
TEMPLATE_TEST_CASE("erase(): exception (out of range)", "", char, int, double) {
    Container<TestType> box1 { 65, 66, 67, 68 };

    // ---------------------check for maxrange +1
    bool flag = false;
    try {
        // attempt to delete last element with out of range
        box1.erase(box1.end() + 1);
    }
    catch(const std::out_of_range& error) {
        flag = true;
    }
    CHECK(flag == true);

    // ---------------------check for minrange -1
    flag = false;
    try {
        box1.erase(box1.begin() - 1);
    }
    catch(const std::out_of_range& error) {
        flag = true;
    }
    CHECK(flag == true);

}

TEMPLATE_TEST_CASE("clear()", "", char, int, double) {
    const Container<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    Container<TestType> box1 { REF };
    CHECK(box1.size() == REF.size());
    box1.clear();
    CHECK(box1.size() == 0);
}

TEMPLATE_TEST_CASE("swap(Container&)", "", char, int, double) {
    const Container<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    Container<TestType> box1 { REF };
    Container<TestType> box2;

    box1.swap(box2);

    CHECK(box1.empty() == true);
    REQUIRE(box2.size() == REF.size());

    CHECK(std::equal(box1.begin(), box1.begin(), REF.begin(), REF.end()) == false);
    CHECK(std::equal(box2.begin(), box2.end(), REF.begin(), REF.end()) == true);
}

TEMPLATE_TEST_CASE("find(const value_type&, pointer)", "", char, int, double) {
    Container<TestType> box1 { 42, 65, 66, 67, 42, 68, 69, 42 };

    CHECK(box1.find(TestType{42}) == box1.begin());
    CHECK(box1.find(TestType{42}, box1.begin() + 1) == box1.begin() + 4);
    CHECK(box1.find(TestType{42}, box1.begin() + 5) == box1.begin() + 7);
    CHECK(box1.find(TestType{73}) == box1.end());
}

TEMPLATE_TEST_CASE("bool operator==(const Container&, const Container&)", "", char, int, double) {
    const Container<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    Container<TestType> box1{ REF };
    Container<TestType> box2{ REF };
    Container<TestType> box3{ REF };

    CHECK((box1 == box2) == true);

    *(box2.end() - 2) = 42;
    CHECK((box1 == box2) == false);

    box3.push_back(42);
    CHECK((box1 == box2) == false);
}

TEMPLATE_TEST_CASE("bool operator!=(const Container&, const Container&)", "", char, int, double) {
    const Container<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    Container<TestType> box1 { REF };
    Container<TestType> box2 { REF };
    Container<TestType> box3 { REF };

    CHECK((box1 != box2) == false);

    *(box2.end() - 2) = 42;
    CHECK((box1 != box2) == true);

    box3.push_back(42);
    CHECK((box1 != box2) == true);
}

TEMPLATE_TEST_CASE("Container operator+(const Container&, const Container&)", "", char, int, double) {
    const Container<TestType> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    const Container<TestType> box1{};
    const Container<TestType> box2{ REF };

    Container<TestType> box3 = box1 + box2;

    CHECK(box3.begin() != box1.begin());
    CHECK(box3.begin() != box2.begin());
    CHECK(std::equal(box3.begin(), box3.end(), REF.begin(), REF.end()) == true);
}

TEMPLATE_TEST_CASE("Container SWAP", "", char, int, double) {
    Container<TestType> box1 { 65, 66, 67 };
    Container<TestType> box2 { 75, 76, 77 };


    for (int i = 65; i <= 67; ++i) {
        CHECK(*(box1.begin() + i - 65) == i);
    }

    for (int j = 75; j <= 77; ++j) {
        CHECK(*(box2.begin() + j - 75) == j);
    }

    box1.swap(box2);

    for (int i = 65; i <= 67; ++i) {
        CHECK(*(box2.begin() + i - 65) == i);
    }

    for (int j = 75; j <= 77; ++j) {
        CHECK(*(box1.begin() + j - 75) == j);
    }

}

TEST_CASE("std::ostream& operator<<(std::ostream&, const Container<char>&)") {
    const Container<char> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    std::ostringstream output{};
    Container<char> box1{};
    Container<char> box2 { REF };

    output << box1;

    CHECK(output.str() == "{}");

    output.str("");

    output << box2;

    CHECK(output.str() == "{A,B,C,D,E,F,G,H}");
}

TEST_CASE("std::ostream& operator<<(std::ostream&, const Container<int>&)") {
    const Container<int> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    std::ostringstream output{};
    Container<int> box1{};
    Container<int> box2 { REF };

    output << box1;

    CHECK(output.str() == "{}");

    output.str("");

    output << box2;

    CHECK(output.str() == "{65,66,67,68,69,70,71,72}");
}

TEST_CASE("std::ostream& operator<<(std::ostream&, const Container<double>&)") {
    const Container<double> REF { 65, 66, 67, 68, 69, 70, 71, 72 };

    std::ostringstream output{};
    output << std::fixed << std::showpoint << std::setprecision(1);

    Container<double> box1{};
    Container<double> box2 { REF };

    output << box1;

    CHECK(output.str() == "{}");

    output.str("");

    output << box2;

    CHECK(output.str() == "{65.0,66.0,67.0,68.0,69.0,70.0,71.0,72.0}");
}

TEST_CASE("std::ostream& operator<<(std::ostream&, const Container<std::string>&)") {
    const Container<std::string> REF {
        "Alpha", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf"
    };
    std::ostringstream output{};

    Container<std::string> box1{};
    Container<std::string> box2{ REF };

    output << box1;

    CHECK(output.str() == "{}");

    output.str("");

    output << box2;

    CHECK(output.str() == "{Alpha,Bravo,Charlie,Delta,Echo,Foxtrot,Golf}");
}

TEST_CASE("operator[char]") {
    const Container<char> box1 { 'a', 'b', 'c' };
    std::ostringstream output{};
    output << box1[1];
    CHECK(output.str() == "b");
}

TEST_CASE("operator[string]") {
    const Container<std::string> box1 { "alpha", "beta", "gamma" };
    std::ostringstream output{};
    output << box1[1];
    CHECK(output.str() == "beta");
}

TEST_CASE("operator[int]") {
    const Container<int> box1 { 1, 2, 3 };
    std::ostringstream output{};
    output << box1[1];
    CHECK(output.str() == "2");
}

TEST_CASE("operator[double]") {
    const Container<double> box1 { 1, 2, 3 };
    std::ostringstream output{};
    output << std::fixed << std::showpoint << std::setprecision(1);
    output << box1[1];
    CHECK(output.str() == "2.0");
}

TEMPLATE_TEST_CASE("memberfunction_at()", "", char, int, double) {
    Container<TestType> box1 { 1, 2, 3, 4 };
    std::ostringstream output{};
    output << std::fixed << std::showpoint << std::setprecision(0);
    auto compnum = box1.at(1);
    CHECK(compnum == 2);
}

/* EOF */

