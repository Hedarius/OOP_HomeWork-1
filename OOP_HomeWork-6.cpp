#include <iostream>

class Car {
private:
	std::string car1;

};

std::ostream& endll(std::ostream &stream) {
	std::cout << std::endl << std::endl;
	return stream;
}

int main() {
	int num;
	std::cout << "Enter number : ";

	while(!(std::cin >> num) || std::cin.get() != '\n') {
		std::cin.clear();
		std::cin.ignore(9999, '\n');
		std::cin.sync();
		std::cout << "Incorrect input!"<< std::endl << "Enter number : ";
		std::cin >> num;
	}

	std::cout << endll << "Hello my dear Friend" << endll << "How are you?";

	return 0;
}

// Задания по игре сделаю в следующем дз