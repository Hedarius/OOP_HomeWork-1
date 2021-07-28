#include <iostream>
#include <cstdint>

class Power {
private:
	int m_number;
	int m_degree;
public:
	void Set(int num, int degree)
	{
		m_number = num;
		m_degree = degree;
	}
	void print() { std::cout << pow(m_number, m_degree); }
};

class RGBA {
private:
	uint8_t m_red;
	uint8_t m_green;
	uint8_t m_blue;
	uint8_t m_alpha;

public:
	RGBA() {
		m_red = 0;
		m_green = 0;
		m_blue = 0;
		m_alpha = 255;
	}

	RGBA(int red, int green, int blue, int alpha)
		: m_red(red), m_green(green), m_blue(blue), m_alpha(alpha) {
	}

	void print() { std::cout << +m_red << " " << +m_green << " " << +m_blue << " " << +m_alpha; }
};

class Stack {
private:
	int m_arr[10];
	int m_top;

public:
	void reset() {
		m_top = 0;
		for (int i = 0; i < 10; i++) {
			m_arr[i] = 0;
		}
	}

	bool push(int value) {
		if (m_top == 10) {
			return false;
		}

		m_arr[m_top++] = value;
		return true;
	}

	int pop() {
		if (m_top > 0) {
			int lastNum = m_arr[m_top - 1];
			--m_top;
			return lastNum;
		}
	}

	void print() {
		std::cout << "( ";
		for (int i = 0; i < m_top; i++) {
			std::cout << m_arr[i] << " ";
		}
		std::cout << ")" << std::endl;
	}
};


int main() {
	Power power;
	power.Set(5, 5);
	power.print();

	std::cout << std::endl;

	RGBA rgba;
	rgba.print();

	std::cout << std::endl;

	Stack stack;
	stack.reset();
	stack.print();

	stack.push(3);
	stack.push(7);
	stack.push(5);
	stack.print();

	stack.pop();
	stack.print();

	stack.pop();
	stack.pop();
	stack.print();

	return 0;
}