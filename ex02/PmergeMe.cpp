#include "PmergeMe.hpp"


bool	isInputValid(int ac, char **arg, std::vector<int> &vec, std::deque<int> &deque)
{
	std::string			word;
	std::stringstream	ss;
	long	l;

    for (int i = 1; i < ac; i++)
        ss << arg[i] << " ";
	
    while (ss >> word)
	{   
		l = strtol(word.c_str(), NULL, 10);
		if (l >= 0 && l < INT_MAX)
		{
			vec.push_back(l);
			deque.push_back(l);
		}
		else
		{
			std::cout << word <<  " ";
			return (false);
		}
	}
	return(true);
}