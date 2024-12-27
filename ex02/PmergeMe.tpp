#include "PmergeMe.hpp"
#include <cstdlib>
#include <limits>

template <typename T>
void PmergeMe::MergeSort(T &list, int left, int right, int threshold) {
	clock_t start;
	if (left == 0 && right == static_cast<int>(list.size()) - 1)
		start = clock();

	if (right - left + 1 <= threshold) {
		insertionSort(list, left, right);
		return;
	}

	int mid = left + (right - left) / 2;
	MergeSort(list, left, mid, threshold);
	MergeSort(list, mid + 1, right, threshold);
	Merge(list, left, mid, right);
}

template <typename T>
void PmergeMe::Merge(T &list, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	std::vector<int> L(n1);
	std::vector<int> R(n2);

	for (int i = 0; i < n1; ++i)
		L[i] = list[left + i];
	for (int i = 0; i < n2; ++i)
		R[i] = list[mid + 1 + i];

	int i = 0;
	int j = 0;
	int k = left;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			list[k] = L[i];
			++i;
		} else {
			list[k] = R[j];
			++j;
		}
		++k;
	}

	while (i < n1) {
		list[k] = L[i];
		++i;
		++k;
	}

	while (j < n2) {
		list[k] = R[j];
		++j;
		++k;
	}
}

template <typename T>
void PmergeMe::insertionSort(T &list, int left, int right) {
	clock_t start = clock();
	for (int i = left + 1; i <= right; ++i) {
		int key = list[i];
		int j = i - 1;

		while (j >= left && list[j] > key) {
			list[j + 1] = list[j];
			--j;
		}
		list[j + 1] = key;
	}
	clock_t end = clock();
	double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
	processTime_ += time;
}

template <typename T>
void PmergeMe::sortList(T &list) {
	int threshold = 10;
	MergeSort(list, 0, list.size() - 1, threshold);
}

template <typename T>
void PmergeMe::printList(const T list) {
	for (size_t i = 0; i < list.size();i++)
		std::cout << list[i] << " ";
}

template <typename T>
double PmergeMe::size(const T list) {
	size_t i = 0;
	while (i < list.size())
		i++;
	return i;
}

template <typename T>
void PmergeMe::printProcessTime(const T list) {
	std::cout << "Time to process a range of " << list.size() << " elements with std::deque container: " << processTime_ << " us" << std::endl;
}

template <typename T>
T PmergeMe::processInput(int argc, char** input) {
	T list;
	for (int i = 1; i < argc; i++) {
		std::string current = input[i];

		if (current.empty())
			throw std::runtime_error("Invalid input (empty)");

		for (size_t j = 0; j < current.size(); ++j)
			if (!std::isdigit(current[j]))
				throw std::runtime_error("Invalid input (contains non-numeric characters or negative value): " + current);

		long value = std::atoll(current.c_str());
		if (value < 0 || value > std::numeric_limits<int>::max())
			throw std::runtime_error("Input value out of range or negative: " + current);

		for (size_t j = 0; j < list.size(); ++j)
			if (list[j] == static_cast<int>(value))
				throw std::runtime_error("Duplicate value detected: " + current);

		list.push_back(std::atoi(current.c_str()));
	}
	return list;
}
