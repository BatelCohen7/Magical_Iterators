#include "MagicalContainer.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace ariel;
using namespace std;

    static bool IsPrime(int num) {
        if (num <= 1) {
            return false;
        }
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }

    // MagicalContainer
    namespace ariel {
        void MagicalContainer::updateSortedElements(){
            sortedElements.clear();
            sortedElements = mainElements;
            sort(sortedElements.begin(), sortedElements.end());
        }

        void MagicalContainer::updateAlternatingElements(){
            alternatingElements.clear();
            bool direction = true;
            for (size_t i = 0, j = mainElements.size() - 1; i <= j;) {
                if( j == 0){
                    alternatingElements.push_back(mainElements[i]);
                    break;
                }
                if(direction){
                    alternatingElements.push_back(mainElements[i]);
                    ++i;
                }
                else{
                    alternatingElements.push_back(mainElements[j]);
                    --j;
                }
                direction = !direction;
            }
            
        }
        
        void MagicalContainer::updatePrimeElements(){
            primeElements.clear();
            for (auto &elem : mainElements) {
                if (IsPrime(elem)) {
                    primeElements.push_back(elem);
                }
            }
        }

        void MagicalContainer::addElement(int e) {
            if (find(mainElements.begin(), mainElements.end(), e) == mainElements.end()) {
                mainElements.push_back(e);
                
                updateSortedElements();
                updateAlternatingElements();
                updatePrimeElements();
            }
        }

        void MagicalContainer::removeElement(int e)
        {
            auto it = find(mainElements.begin(), mainElements.end(), e);
            if (it != mainElements.end())
            {
                mainElements.erase(it);

                updateSortedElements();
                updateAlternatingElements();
                updatePrimeElements();
            }
            else {
                throw runtime_error("Element not found");
            }
        }


        size_t MagicalContainer::getSize() const{
            return mainElements.size();
        }

        vector<int> MagicalContainer::getAllElements() const {
            return mainElements;
        }
    }

    // AscendingIterator Implementation
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container)
        : containerRef(container), index(0) {}

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other)
    : containerRef(other.containerRef), index(other.index) {
    
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other) {
        if(&this->containerRef != &other.containerRef)
        {
            throw std::runtime_error("dif container");
        }
        if (this == &other) {
            return *this;
        }

        containerRef = other.containerRef;
        index = other.index;

        // Perform any necessary deep copying of member variables

        return *this;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
        if(index >= containerRef.sortedElements.size()) {
            throw runtime_error("Index out of range");
        }
        ++index;
        return *this;
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
        return &containerRef == &other.containerRef && index == other.index;
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
        return &containerRef == &other.containerRef && index > other.index;
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
        return &containerRef == &other.containerRef && index < other.index;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
        return !(*this == other);
    }

    int MagicalContainer::AscendingIterator::operator*() const {
        if(index >= containerRef.sortedElements.size()) {
            throw out_of_range("Index out of range");
        }
        return containerRef.sortedElements[index];
    }


    // SideCrossIterator Implementation
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container)
        : containerRef(container), index(0) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other)
    : containerRef(other.containerRef), index(other.index) {
    
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other) {
        if(&this->containerRef != &other.containerRef)
        {
            throw std::runtime_error("dif container");
        }
        if (this == &other) {
            return *this;
        }

        containerRef = other.containerRef;
        index = other.index;

        // Perform any necessary deep copying of member variables

        return *this;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
        if(index >= containerRef.alternatingElements.size()) {
            throw runtime_error("Index out of range");
        }
        ++index;
        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {
        return &containerRef == &other.containerRef && index == other.index;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {
        return !(*this == other);
    }
    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const{
        return &containerRef == &other.containerRef && index > other.index;
    }
    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const{
        return &containerRef == &other.containerRef && index < other.index;
    }

    int MagicalContainer::SideCrossIterator::operator*() const {
        if(index >= containerRef.alternatingElements.size()) {
            throw out_of_range("Index out of range");
        }
        cout << containerRef.alternatingElements[index] << endl;
        return containerRef.alternatingElements[index];
    }


    // PrimeIterator Implementation
    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container)
        : containerRef(container), index(0) {}

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other)
    : containerRef(other.containerRef), index(other.index) {
    
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other) {
        if(&this->containerRef != &other.containerRef)
        {
            throw std::runtime_error("dif container");
        }
        if (this == &other) {
            return *this;
        }

        containerRef = other.containerRef;
        index = other.index;

        // Perform any necessary deep copying of member variables

        return *this;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
        if(index >= containerRef.primeElements.size()) {
            throw runtime_error("Index out of range");
        }
        ++index;
        return *this;
    }

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const {
        return &containerRef == &other.containerRef && index == other.index;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const {
        return !(*this == other);
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const{
        return &containerRef == &other.containerRef && index > other.index;
    }
    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const{
        return &containerRef == &other.containerRef && index < other.index;
    }

    int MagicalContainer::PrimeIterator::operator*() const {
        if(index >= containerRef.primeElements.size()) {
            throw out_of_range("Index out of range");
        }
        return containerRef.primeElements[index];
    }
