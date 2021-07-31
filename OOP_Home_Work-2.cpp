#include <iostream>
#include <string>
#include <sstream>

class Person {
protected:
	std::string m_name;
	int m_age;
	std::string m_gender;
	int m_weight;

public:
	Person() : m_name(""), m_age(0), m_gender(""), m_weight(0) {
		
	}

	Person(std::string name, int age, std::string gender, int weight) {
		this->m_name = name;
		this->m_age = age;
		this->m_gender = gender;
		this->m_weight = weight;
	}

	friend class Student;
};

class Student : public Person {
private:
	int m_year;
	int m_id;
	static int s_idGenerator;

public:
	Student() : m_year(0), m_id(0) {

	}

	Student(std::string name, int age, std::string gender, int weight, int year)
		: Person(name, age, gender, weight), m_year(year) {
		s_idGenerator++;
		m_id = s_idGenerator;
	}
	static int getID() { 
		return s_idGenerator; }

	std::string getStudentInfo() {
		std::ostringstream m_id;
		m_id << m_name << " " << m_age << " "
			<< m_gender << " " << m_weight << " " << m_year;
		return m_id.str();
	}
};

int Student::s_idGenerator = 0;

class Fruit {
protected:
	std::string m_name;
	std::string m_color;
public:
	Fruit() : m_name(""), m_color() {

	}

	Fruit(std::string name, std::string color) {
		m_name = name;
		m_color = color;
	}
};

class Apple : public Fruit {
public:
	Apple() {

	}

	std::string getName() {
		return "apple";
	}

	Apple(std::string color) {
		m_color = color;
	}

	std::string getColor() {
		return m_color;
	}
};

class Banana : public Fruit {
public:
	std::string getName() {
		return "banana";
	}

	std::string getColor() {
		return "yellow";
	}
};

class GrannySmith : public Apple {
public:
	GrannySmith() {
	}

	std::string getName() {
		return "Granny Smith apple";
	}

	std::string getColor() {
		return "green";
	}
};

int main() {
	int id;
	const int size = 5;
	Student stud;
	Student stud_list[size] {
			Student("Anton", 22, "male", 83, 2012),
			Student("Arina", 19, "female", 45, 2014),
			Student("Ksenia", 20, "female", 47, 2013),
			Student("Oleg", 21, "male", 79, 2014),
			Student("Anastasia", 20, "female", 47, 2014) };

	std::cout << "Number of students : " << stud.getID() << std::endl;
	std::cout << "Enter student ID(0-4) : ";
	std::cin >> id;
	std::cout << stud_list[id].getStudentInfo();

	std::cout << std::endl << std::endl;

	Apple a("red");
	Banana b;
	GrannySmith c;

	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
	std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

	return 0;
}