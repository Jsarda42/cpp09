#include "PmergeMe.hpp"
#include <iostream>
#include <vector>

int main(int argc, char **argv) {

	if (argc < 3) {
		std::cerr << "Error : Arguments must be atleast 2\n";
		return 1;
	}
	PmergeMe sorter;
	std::vector<int> vectorList;
	std::deque<int> dequeList;

	try {
		vectorList = sorter.processInput<std::vector<int> >(argc, argv);
		std::cout << "Before : ";
		sorter.printList(vectorList);
		std::cout << std::endl;
		sorter.sortList(vectorList);
		std::cout << "After : ";
		sorter.printList(vectorList);
		std::cout << std::endl;
		dequeList = sorter.processInput<std::deque<int> >(argc, argv);
		sorter.sortList(dequeList);
		sorter.printProcessTime(vectorList);
		sorter.printProcessTime(dequeList);
	} 
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	}
	return 0;
}
