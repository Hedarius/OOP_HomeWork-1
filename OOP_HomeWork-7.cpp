#include <iostream>

class Date {
private:
	int m_day;
	int m_month;
	int m_year;
public:
	Date(int const& day, int const& month, int const& year) : m_day(day), m_month(month), m_year(year) {}

	~Date() {}

	int getDay() {
		return m_day;
	}
	int getMonth() {
		return m_month;
	}
	int getYear() {
		return m_year;
	}

	friend std::ostream& operator<< (std::ostream& out, const Date& date);
};

std::ostream& operator<< (std::ostream& out, const Date& date) {
	out << "Date : " << date.m_day << "." << date.m_month << "." << date.m_year;
	return out;
}

class today_ptr {
	Date* m_ptr;
public:
	today_ptr(Date* ptr=nullptr) : m_ptr(ptr) {}
	~today_ptr() {
		delete m_ptr;
	}

	Date& operator*() const { return *m_ptr; }
	Date* operator->() const { return m_ptr; }
	today_ptr& operator=(today_ptr& t_ptr) {
		if (this == &t_ptr) {
			return *this;
		}
		delete m_ptr;
		m_ptr = t_ptr.m_ptr;
		t_ptr.m_ptr = nullptr;
		return *this;
	}
	bool Null() const {
		return m_ptr == nullptr;
	}
};

today_ptr& Compare(today_ptr& ptr1, today_ptr& ptr2) {
	if (ptr1->getYear() > ptr2->getYear()) {
		return ptr1;
	}
	else if(ptr1->getYear() < ptr2->getYear()) {
		return ptr2;
	}
	else {
		if (ptr1->getMonth() > ptr2->getMonth()) {
		return ptr1;
		}
		else if (ptr1->getMonth() < ptr2->getMonth()) {
		return ptr2;
		}
		else {
			if (ptr1->getDay() > ptr2->getDay()) {
				return ptr1;
			}
			else if (ptr1->getDay() < ptr2->getDay()) {
			return ptr2;
			}
			else {
				std::cout << "dates are equal";
				return ptr1;
			}
		}
	}
}

void Obmen(today_ptr& today, today_ptr& date) {
	today_ptr ptr;
	ptr = today;
	today = date;
	date = ptr;
}

int main() {
	today_ptr today = new Date(17, 8, 2021);
	today_ptr date;
	std::cout << today->getDay() << "." << today->getMonth() << "." << today->getYear() << std::endl;
	std::cout << *today << std::endl;
	date = today;
	std::cout << "today null? -> " << today.Null() << std::endl;
	std::cout << "date null? -> " << today.Null() << std::endl;
	today_ptr date1 = new Date(4, 11, 2015);
	today_ptr date2 = new Date(15, 9, 2019);
	std::cout << *Compare(date1, date2) << std::endl;
	Obmen(date1, date2);
	std::cout << *date1 << std::endl;
	std::cout << *date2 << std::endl;

	return 0;
}