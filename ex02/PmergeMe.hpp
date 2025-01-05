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
    bool comp(T lv, T rv) {
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
        int pair_units_nbr = container.size() / pair_level;
        if (pair_units_nbr < 2)
            return;
        bool is_odd = pair_units_nbr % 2 == 1;

        _sort_pairs(container, pair_level);
        _merge_insertion_sort(container, pair_level * 2);
        T main;
        T pend;
        _initialize_main_and_pend(container, pair_level, main, pend);
        _insert_pend_into_main(main, pend);
        _insert_remaining_elements(main, pend, is_odd, next(container.begin(), pair_level * pair_units_nbr), pair_level);
        _replace_container_values(container, main, pair_level);
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

    template <typename T>
    void _sort_pairs(T &container, int pair_level) {
        typedef typename T::iterator Iterator;

        int pair_units_nbr = container.size() / pair_level;
        bool is_odd = pair_units_nbr % 2 == 1;

        Iterator start = container.begin();
        Iterator last = next(container.begin(), pair_level * pair_units_nbr);
        Iterator end = next(last, -(is_odd * pair_level));

        int jump = 2 * pair_level;
        for (Iterator it = start; it != end; std::advance(it, jump)) {
            Iterator this_pair = next(it, pair_level - 1);
            Iterator next_pair = next(it, pair_level * 2 - 1);
            if (*this_pair > *next_pair)
                _swap_pair<T>(this_pair, pair_level);
        }
        std::cout << "After sorting pairs: ";
        for (const auto &elem : container) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    template <typename T>
    void _initialize_main_and_pend(T &container, int pair_level, T &main, T &pend) {
        int pair_units_nbr = container.size() / pair_level;

        main.push_back(*next(container.begin(), pair_level - 1));
        main.push_back(*next(container.begin(), pair_level * 2 - 1));

        for (int i = 4; i <= pair_units_nbr; i += 2) {
            pend.push_back(*next(container.begin(), pair_level * (i - 1) - 1));
            main.push_back(*next(container.begin(), pair_level * i - 1));
        }
        std::cout << "After initializing main and pend:\nMain: ";
        for (const auto &elem : main) {
            std::cout << elem << " ";
        }
        std::cout << "\nPend: ";
        for (const auto &elem : pend) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    template <typename T>
    void _insert_pend_into_main(T &main, T &pend) {
        int prev_jacobsthal = jacobsthal_number(1);

        for (int k = 2;; ++k) {
            int curr_jacobsthal = jacobsthal_number(k);
            int jacobsthal_diff = curr_jacobsthal - prev_jacobsthal;

            if (jacobsthal_diff > static_cast<int>(pend.size())) {
                break;
            }

            auto pend_it = pend.begin();
            for (int i = 0; i < jacobsthal_diff && pend_it != pend.end(); ++i) {
                auto insert_it = std::upper_bound(main.begin(), main.end(), *pend_it);
                main.insert(insert_it, *pend_it);
                pend_it = pend.erase(pend_it);
            }

            prev_jacobsthal = curr_jacobsthal;
        }
        std::cout << "After inserting pend into main:\nMain: ";
        for (const auto &elem : main) {
            std::cout << elem << " ";
        }
        std::cout << "\nPend: ";
        for (const auto &elem : pend) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    template <typename T>
    void _insert_remaining_elements(T &main, T &pend, bool is_odd, typename T::iterator end, int pair_level) {
        for (const auto &elem : pend) {
            auto insert_it = std::upper_bound(main.begin(), main.end(), elem);
            main.insert(insert_it, elem);
        }

        if (is_odd) {
            auto odd_pair = next(end, pair_level - 1);
            auto insert_it = std::upper_bound(main.begin(), main.end(), *odd_pair);
            main.insert(insert_it, *odd_pair);
        }
        std::cout << "After inserting remaining elements:\nMain: ";
        for (const auto &elem : main) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    template <typename T>
    void _replace_container_values(T &container, T &main, int pair_level) {
        T copy;
        (void)pair_level;
        for (auto it = main.begin(); it != main.end(); ++it) {
            copy.push_back(*it);
        }

        std::cout << "Copy after replacing container values: ";
        for (const auto &elem : copy) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;

        std::copy(copy.begin(), copy.end(), container.begin());
        std::cout << "After replacing container values: ";
        for (const auto &elem : container) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
};
