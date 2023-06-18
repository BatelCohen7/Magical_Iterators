#include "doctest.h"
#include "MagicalContainer.hpp"

using namespace ariel;

TEST_CASE("Functional Tests and Errors") {
    MagicalContainer container;

    SUBCASE("Empty Container") {
        CHECK(container.size() == 0);
        CHECK(container.getAllElements().empty());

        CHECK_NOTHROW(container.removeElement(5));
        CHECK_THROWS_AS(container.removeElement(5), std::runtime_error);
        CHECK_THROWS_WITH(container.removeElement(5), "Element not found");

        DOCTEST_SUBCASE("Iterators") {
            MagicalContainer::AscendingIterator ascIter(container);
            CHECK_THROWS_AS(*ascIter, std::out_of_range);
            CHECK_THROWS_WITH(*ascIter, "Index out of range");

            MagicalContainer::PrimeIterator primeIter(container);
            CHECK_THROWS_AS(*primeIter, std::out_of_range);
            CHECK_THROWS_WITH(*primeIter, "Index out of range");

            MagicalContainer::SideCrossIterator crossIter(container);
            CHECK_THROWS_AS(*crossIter, std::out_of_range);
            CHECK_THROWS_WITH(*crossIter, "Index out of range");
        }
    }

    SUBCASE("Adding and Removing Elements") {
        CHECK_NOTHROW(container.addElement(1));
        CHECK_NOTHROW(container.addElement(2));
        CHECK_NOTHROW(container.addElement(3));
        CHECK(container.size() == 3);

        CHECK_NOTHROW(container.addElement(1)); // Duplicate element, should not be added
        CHECK(container.size() == 3);

        CHECK_NOTHROW(container.removeElement(2));
        CHECK(container.size() == 2);

        CHECK_NOTHROW(container.removeElement(1));
        CHECK(container.size() == 1);

        CHECK_THROWS_AS(container.removeElement(2), std::runtime_error);
        CHECK_THROWS_WITH(container.removeElement(2), "Element not found");
    }

    SUBCASE("Iterators") {
        // Add elements to the container
        container.addElement(5);
        container.addElement(2);
        container.addElement(10);
        container.addElement(7);

        MagicalContainer::AscendingIterator ascIter(container);
        MagicalContainer::PrimeIterator primeIter(container);
        MagicalContainer::SideCrossIterator crossIter(container);

        DOCTEST_SUBCASE("Ascending Iterator") {
            auto it = ascIter.begin();
            CHECK(*it == 2);
            ++it;
            CHECK(*it == 5);
            ++it;
            CHECK(*it == 7);
            ++it;
            CHECK(*it == 10);
            ++it;
            CHECK(it == ascIter.end());
            CHECK_THROWS_AS(*it, std::out_of_range);
            CHECK_THROWS_WITH(*it, "Index out of range");
        }

        DOCTEST_SUBCASE("Prime Iterator") {
            auto it = primeIter.begin();
            CHECK(*it == 2);
            ++it;
            CHECK(*it == 5);
            ++it;
            CHECK(it == primeIter.end());
            CHECK_THROWS_AS(*it, std::out_of_range);
            CHECK_THROWS_WITH(*it, "Index out of range");
        }

        DOCTEST_SUBCASE("Side Cross Iterator") {
            auto it = crossIter.begin();
            CHECK(*it == 2);
            ++it;
            CHECK(*it == 10);
            ++it;
            CHECK(*it == 5);
            ++it;
            CHECK(*it == 7);
            ++it;
            CHECK(it == crossIter.end());
            CHECK_THROWS_AS(*it, std::out_of_range);
            CHECK_THROWS_WITH(*it, "Index out of range");
        }
    }
}
