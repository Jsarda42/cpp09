#pragma once
#include <iostream>
#include <vector>
#include <deque>

class PmergeMe {

	private:
		float processTime_;

	public:
		PmergeMe(void);
		// PmergeMe(const PmergeMe& cpy);
		// PmergeMe& operator=(const PmergeMe& rhs);
		~PmergeMe(void);

		template <typename T>
		void printList(const T list);

		template <typename T>
		void sortList(T &list);

		template <typename T>
		void insertionSort(T &List, int left, int right);

		template <typename T>
		void Merge(T &List, int left, int mid, int right);

		template <typename T>
		double size(const T List);

		template <typename T>
		void MergeSort(T &list, int left, int right, int threshold);

		template <typename T>
		void printProcessTime(const T list);

		template <typename T>
		T processInput(int argc, char** input);
};

#include "PmergeMe.tpp"
