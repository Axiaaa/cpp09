#include "PmergeMe.hpp"
#include <iomanip>

int main(int ac, char **av)
{
	std::vector<int> vecToSort;
	std::deque<int> dequeToSort;

	if (ac < 1 || !isInputValid(ac, av, vecToSort, dequeToSort))
    {
        std::cerr << "Invalid input" << std::endl;
        return 1;
    }
	
	std::cout << "Before:	";
 	for (std::vector<int>::iterator it = vecToSort.begin(); it != vecToSort.end(); it++)
		std::cout << *it << " ";

	std::clock_t start_time = std::clock();
    mergeInsertSort(vecToSort);
    std::clock_t end_time = std::clock();
	
	std::cout << "\nAfter:	";
 	for (std::vector<int>::iterator it = vecToSort.begin(); it != vecToSort.end(); it++)
		std::cout << *it << " ";

	double res_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "\nTime to process a range of " << vecToSort.size() << " elements with std::vector<int> sort: " << std::fixed << std::setprecision(6) << res_time << " us" << std::endl;
	
    
	start_time = std::clock();
    mergeInsertSort(dequeToSort);
    end_time = std::clock();

    res_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << dequeToSort.size() << " elements with std::deque<int> sort: " << std::fixed << std::setprecision(6) << res_time << " us" << std::endl;

    return 0;
}