#include <iostream>
#include <string>

class Figure {
	virtual void area() = 0;
};

class Parallelogram : public Figure {
protected:
	int m_base;
	int m_height;

public:
	Parallelogram(int base, int height) : m_base(base), m_height(height) {
		base;
		height;
	}

	void area() override {
		std::cout << "The parallelogram area is : " << m_base * m_height << std::endl;
	}
};

class Circle : public Figure {
private:
	double m_radius;
	double P{3.1415};

public:
	Circle(double radius) : m_radius(radius) {
	}

	void area() override {
		std::cout << "The area of the circle is : " << P * (m_radius * m_radius) << std::endl;
	}
};

class Rectangle : public Parallelogram {
public:
	Rectangle(int base, int height) : Parallelogram(base, height) {
	}

	void area() override {
		std::cout << "The area of the triangle is : " << m_base * m_height << std::endl;
	}
};

class Square : public Parallelogram {
public:
	Square(int base, int height) : Parallelogram(base, height) {
	}

	void area() override {
		std::cout << "The square area is : " << m_base * m_height << std::endl;
	}
};

class Rhombus : public Parallelogram {
public:
	Rhombus(int base, int height) : Parallelogram(base, height) {
	}

	void area() override {
		std::cout << "The area of the rhombus : " << m_base * m_height << std::endl;
	}
};

class Car {
protected:
	std::string m_company;
	std::string m_model;

public:
	Car() { }

	Car(std::string company, std::string model) : m_company(company), m_model(model) {
	}
};

class PassengerCar : virtual public Car {
public:
	PassengerCar() { }
 
	PassengerCar(std::string company, std::string model) : Car(company, model) {
	}

	void print() {
		std::cout << "Passenger car info: \n\t Company: " << m_company << "\n\t Model: " << m_model << std::endl;
	}
};

class Bus : public virtual Car {
public:
	Bus() { }

	Bus(std::string company, std::string model) : Car(company, model) {
	}

	void print() {
		std::cout << "Bus info: \n\t Company: " << m_company << "\n\t Model: " << m_model << std::endl;
	}
};

class Minivan : public PassengerCar, public Bus {
public:
	Minivan(std::string company, std::string model) : PassengerCar::Car(company, model) {
	}

	void print() {
		std::cout << "Minivan info: \n\t Company: " << m_company << "\n\t Model: " << m_model << std::endl;
	}
};

class Fraction {
	int m_num;
	int m_denom;

public:
	Fraction(int num, int denom) {
		if (m_denom == 0) {
			throw std::runtime_error("The denominator cannot be 0");
			this->m_num = num;
			this->m_denom = denom;
		};
	}

	int getNum(int num) const {
		return m_num;
	}

	int getDenom(int denom) const {
		return m_denom;
	}

	bool operator==(const Fraction& other) {
		return this->m_num == other.m_num && this->m_denom == other.m_denom;
	}

	bool operator !=(const Fraction& other) {
		return this->m_num != other.m_num && this->m_denom != other.m_denom;
	}

	bool operator <(const Fraction& other) {
		if (this->m_num >= other.m_num && this->m_denom >= other.m_denom) {
			return false;
		}
		else {
			return true; 
		}
	}

	bool operator >(const Fraction& other) {
		if (this->m_num <= other.m_num && this->m_denom <= other.m_denom) {
			return false;
		}
		else {
			return true;
		}
	}

	friend Fraction operator + (const Fraction&f1, const Fraction &f2) {
		return Fraction(f1.m_num * f2.m_denom + f2.m_num * f1.m_denom, f1.m_num * f2.m_num);
	}

	friend Fraction operator - (const Fraction& f1, const Fraction& f2) {
		return Fraction(f1.m_num * f2.m_denom - f2.m_num * f1.m_denom, f1.m_num * f2.m_num);
	}

	friend Fraction operator * (const Fraction& f1, const Fraction& f2) {
		return Fraction(f1.m_num * f2.m_num, f1.m_denom * f2.m_denom);
	}

	friend Fraction operator / (const Fraction& f1, const Fraction& f2) {
		return Fraction(f1.m_num / f2.m_num, f1.m_denom * f2.m_denom);
	}
};

enum CardsValue {
	Jack = 10,
	Queen = 10,
	King = 10,
	Ace = 1
};

enum Suits {
	Heart,
	Diamond,
	Club,
	Spade
};

class Card {
protected:
	enum CardsValue {
		two = 2,
		three = 3,
		four = 4,
		five = 5,
		six = 6,
		seven = 7,
		eight = 8,
		nine = 9,
		ten = 10,
		Jack = 10,
		Queen = 10,
		King = 10,
		Ace = 1
	};

	enum Suits {
		Heart,
		Diamond,
		Club,
		Spade
	};

	bool cardPosition = true;

public:
	Card() {
	}

	bool Flip() {
		if (cardPosition) {
		return false;
		}
	else {
		return true;
	}
	}

	int GetValue() {
		return CardsValue();
	}

};

int main() {

	Parallelogram p(3, 5);
	p.area();

	Circle c(4);
	c.area();

	Rectangle r(5, 8);
	r.area();

	Square s(4, 4);
	s.area();

	Rhombus rom(4, 6);
	rom.area();

	std::cout << std::endl << std::endl;

	PassengerCar pas("Mercedes", "AMG GT S");

	Bus bus("Setra", "S431 DT");

	Minivan mini("KIA","Carnival");

	pas.print();

	bus.print();

	mini.print();

	std::cout << std::endl << std::endl;

	Fraction f1(3, 7);

	Fraction f2(5, 12);

	bool result_1 = f1 == f2;
	
	bool result_2 = f1 != f2;

	bool result_3 = f1 < f2;

	bool result_4 = f1 > f2;

	Fraction f_sum = f1 + f2;

	Fraction f_sub = f1 - f2;

	Fraction f_pro = f1 * f2;

	Fraction f_res = f1 / f2;

	return 0;
}