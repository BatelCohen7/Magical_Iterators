#ifndef MAGICAL_CONTAINER_HPP
#define MAGICAL_CONTAINER_HPP

#include <vector>

namespace ariel {

    class MagicalContainer {
        friend class AscendingIterator;
        friend class SideCrossIterator;
        friend class PrimeIterator;

    public:

        size_t getSize() const;
        class AscendingIterator {
        public:
            AscendingIterator(MagicalContainer& container);

            AscendingIterator(const AscendingIterator& other); // Copy Constructor
            AscendingIterator& operator=(const AscendingIterator& other); // Copy Assignment Operator

            AscendingIterator& operator++();
            bool operator==(const AscendingIterator& other) const;
            bool operator!=(const AscendingIterator& other) const;
            int operator*() const;
            AscendingIterator begin() { return AscendingIterator(containerRef); }
            AscendingIterator end() { auto iter = begin(); iter.index = containerRef.sortedElements.size(); return iter; }
            
            bool operator>(const AscendingIterator& other) const;
            bool operator<(const AscendingIterator& other) const;

        private:
            MagicalContainer& containerRef;
            size_t index;
        };

        class SideCrossIterator {
        public:
            SideCrossIterator(MagicalContainer& container);
            SideCrossIterator(const SideCrossIterator& other); // Copy Constructor
            SideCrossIterator& operator=(const SideCrossIterator& other); // Copy Assignment Operator
            SideCrossIterator& operator++();
            bool operator==(const SideCrossIterator& other) const;
            bool operator!=(const SideCrossIterator& other) const;
            int operator*() const;
            SideCrossIterator begin() { return SideCrossIterator(containerRef); }
            SideCrossIterator end() { auto iter = begin(); iter.index = containerRef.alternatingElements.size(); return iter; }
            bool operator>(const SideCrossIterator& other) const;
            bool operator<(const SideCrossIterator& other) const;
        private:
            MagicalContainer& containerRef;
            size_t index;
        };

        class PrimeIterator {
        public:
            PrimeIterator(MagicalContainer& container);
            PrimeIterator(const PrimeIterator& other); // Copy Constructor
            PrimeIterator& operator=(const PrimeIterator& other); // Copy Assignment Operator
            PrimeIterator& operator++();
            bool operator==(const PrimeIterator& other) const;
            bool operator!=(const PrimeIterator& other) const;
            int operator*() const;
            PrimeIterator begin() { return PrimeIterator(containerRef); }
            PrimeIterator end() { auto iter = begin(); iter.index = containerRef.primeElements.size(); return iter; }
                    
            bool operator>(const PrimeIterator& other) const;
            bool operator<(const PrimeIterator& other) const;
        private:
            MagicalContainer& containerRef;
            size_t index;
        };

        // MagicalContainer class public member functions
        MagicalContainer() = default;
        void addElement(int e);
        void removeElement(int e);
        size_t size() const { return mainElements.size(); }
        std::vector<int> getAllElements() const;

    private:
        std::vector<int> mainElements;
        std::vector<int> sortedElements;
        std::vector<int> alternatingElements;
        std::vector<int> primeElements;

        void updateSortedElements();
        void updateAlternatingElements();
        void updatePrimeElements();
    };

} // namespace ariel

#endif // MAGICAL_CONTAINER_HPP