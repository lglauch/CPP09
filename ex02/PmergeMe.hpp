#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <sstream>
#include <chrono>
#include <cmath>
#include <set>

class PmergeMe {
public:
    PmergeMe();
    PmergeMe(const PmergeMe &old);
    PmergeMe& operator=(const PmergeMe &old);
    ~PmergeMe();

    void printSequence(const std::string &prefix, const std::vector<int> &vec);
    void printSequence(const std::string &prefix, const std::list<int> &lst);

    long jacobsthal_number(long n);

    template <typename T>
    bool comp(const T& lv, const T& rv) {
        return *lv < *rv;
    }

    template <typename T>
    T next(T it, int steps) {
        std::advance(it, steps);
        return it;
    }

    template <typename Container>
    double measureSortTime(Container &container) {
        (void)container;
        auto start = std::chrono::high_resolution_clock::now();
        _merge_insertion_sort(container, 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::micro> duration = end - start;

        return duration.count();
    }

private:
    template <typename T>
    void _merge_insertion_sort(T& container, int pair_level) {
        typedef typename T::iterator Iterator;

        int pair_units_nbr = container.size() / pair_level;
        if (pair_units_nbr < 2)
            return;

        bool is_odd = pair_units_nbr % 2 == 1;

        Iterator start = container.begin();
        Iterator last = next(container.begin(), pair_level * (pair_units_nbr));
        Iterator end = next(last, -(is_odd * pair_level));

        int jump = 2 * pair_level;
        for (Iterator it = start; it != end; std::advance(it, jump)) {
            Iterator this_pair = next(it, pair_level - 1);
            Iterator next_pair = next(it, pair_level * 2 - 1);
            if (*this_pair > *next_pair) {
                _swap_pair<T>(this_pair, pair_level);
            }
        }
        _merge_insertion_sort(container, pair_level * 2);

        std::vector<Iterator> main;
        std::vector<Iterator> pend;

        main.push_back(next(container.begin(), pair_level - 1));
        main.push_back(next(container.begin(), pair_level * 2 - 1));

        for (int i = 4; i <= pair_units_nbr; i += 2) {
            pend.push_back(next(container.begin(), pair_level * (i - 1) - 1));
            main.push_back(next(container.begin(), pair_level * i - 1));
        }

        _merge_and_insert(container, main, pend, is_odd, end, pair_level);
    }

    template <typename T>
    void _merge_and_insert(T& container, std::vector<typename T::iterator>& main, std::vector<typename T::iterator>& pend, bool is_odd, typename T::iterator end, int pair_level) {
        _insert_pend_into_main(container, main, pend, pair_level);
        _insert_remaining_elements(container, main, pend, is_odd, end, pair_level);
        _replace_container_values(container, main, pair_level);
    }

    template <typename T>
    void _insert_pend_into_main(T& container, std::vector<typename T::iterator>& main, std::vector<typename T::iterator>& pend, int pair_level) {
        typedef typename T::iterator Iterator;

        (void)container;
        (void)pair_level;
        int prev_jacobsthal = jacobsthal_number(1);
        int inserted_numbers = 0;
        for (int k = 2;; k++) {
            int curr_jacobsthal = jacobsthal_number(k);
            int jacobsthal_diff = curr_jacobsthal - prev_jacobsthal;
            int offset = 0;
            if (jacobsthal_diff > static_cast<int>(pend.size()))
                break;
            int nbr_of_times = jacobsthal_diff;
            typename std::vector<Iterator>::iterator pend_it = next(pend.begin(), jacobsthal_diff - 1);
            typename std::vector<Iterator>::iterator bound_it =
                next(main.begin(), curr_jacobsthal + inserted_numbers);
            while (nbr_of_times) {
                typename std::vector<Iterator>::iterator idx =
                    std::upper_bound(main.begin(), bound_it, *pend_it, [this](const Iterator& lv, const Iterator& rv) { return comp(lv, rv); });
                typename std::vector<Iterator>::iterator inserted = main.insert(idx, *pend_it);
                nbr_of_times--;
                pend_it = pend.erase(pend_it);
                std::advance(pend_it, -1);
                offset += (inserted - main.begin()) == curr_jacobsthal + inserted_numbers;
                bound_it = next(main.begin(), curr_jacobsthal + inserted_numbers - offset);
            }
            prev_jacobsthal = curr_jacobsthal;
            inserted_numbers += jacobsthal_diff;
            offset = 0;
        }
    }

    template <typename T>
    void _insert_remaining_elements(T& container, std::vector<typename T::iterator>& main, std::vector<typename T::iterator>& pend, bool is_odd, typename T::iterator end, int pair_level) {
        typedef typename T::iterator Iterator;

        (void)container;
        for (size_t i = 0; i < pend.size(); i++) {
            typename std::vector<Iterator>::iterator curr_pend = next(pend.begin(), i);
            typename std::vector<Iterator>::iterator curr_bound =
                next(main.begin(), main.size() - pend.size() + i);
            typename std::vector<Iterator>::iterator idx =
                std::upper_bound(main.begin(), curr_bound, *curr_pend, [this](const Iterator& lv, const Iterator& rv) { return comp(lv, rv); });
            main.insert(idx, *curr_pend);
        }

        if (is_odd) {
            typename T::iterator odd_pair = next(end, pair_level - 1);
            typename std::vector<Iterator>::iterator idx =
                std::upper_bound(main.begin(), main.end(), odd_pair, [this](const Iterator& lv, const Iterator& rv) { return comp(lv, rv); });
            main.insert(idx, odd_pair);
        }
    }

    template <typename T>
    void _replace_container_values(T& container, std::vector<typename T::iterator>& main, int pair_level) {
        typedef typename T::iterator Iterator;

        std::vector<int> copy;
        copy.reserve(container.size());
        for (typename std::vector<Iterator>::iterator it = main.begin(); it != main.end(); it++) {
            for (int i = 0; i < pair_level; i++) {
                Iterator pair_start = *it;
                std::advance(pair_start, -pair_level + i + 1);
                copy.push_back(*pair_start);
            }
        }

        Iterator container_it = container.begin();
        typename std::vector<int>::iterator copy_it = copy.begin();
        while (copy_it != copy.end()) {
            *container_it = *copy_it;
            container_it++;
            copy_it++;
        }
    }

    template <typename T>
    void _swap_pair(typename T::iterator it, int pair_level) {
        auto start = next(it, -pair_level + 1);
        auto end = next(start, pair_level);
        while (start != end) {
            std::iter_swap(start, next(start, pair_level));
            ++start;
        }
    }
};