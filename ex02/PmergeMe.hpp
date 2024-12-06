#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <deque>
#include "limits.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>

bool	isInputValid(int ac, char **av, std::vector<int> &_list, std::deque<int> &_deque);

template <typename T>
void insertionSort(T& container) {
    typename T::iterator it, jt;
    for (it = container.begin() + 1; it != container.end(); ++it) {
        typename T::value_type key = *it;
        jt = it;
        while (jt != container.begin() && *(jt - 1) > key) {
            *jt = *(jt - 1);
            --jt;
        }
        *jt = key;
    }
}

template <typename T>
void merge(T& container, const T& left, const T& right) {
    typename T::iterator it = container.begin();
    typename T::const_iterator itL = left.begin();
    typename T::const_iterator itR = right.begin();

    while (itL != left.end() && itR != right.end()) {
        if (*itL <= *itR) {
            *it = *itL;
            ++itL;
        } else {
            *it = *itR;
            ++itR;
        }
        ++it;
    }

    while (itL != left.end()) {
        *it = *itL;
        ++itL;
        ++it;
    }

    while (itR != right.end()) {
        *it = *itR;
        ++itR;
        ++it;
    }
}

template <typename T>
void mergeInsertSort(T& container) {
    if (container.size() <= 1) {
        return; 
    }

    if (container.size() <= 100) { 
        insertionSort(container);
        return;
    }

    typename T::iterator middle = container.begin();
    std::advance(middle, container.size() / 2); 

    T left(container.begin(), middle);
    T right(middle, container.end());

    mergeInsertSort(left);
    mergeInsertSort(right);

    merge(container, left, right);
}
