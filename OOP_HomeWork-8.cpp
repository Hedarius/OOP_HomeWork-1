#include <iostream>
#include <vector>

class DivistionByZero : public std::runtime_error {
public:
    DivistionByZero(const std::string& what) : std::runtime_error(what) {}
};

template<typename T>
T divide(const T& nominator, const T& denominator) {
    if (denominator == T(0)) {
        throw DivistionByZero("Divistion by Zero");
    }
    return nominator / denominator;
}

class Ex
{
public:
    double x;
    Ex(const double& x_) :x(x_) {}
    ~Ex() {}
};

class Bar
{
private:
    double y;

public:
    Bar() { y = 0; }
    ~Bar() {}
    void set(const double& a)
    {
        if (y + a <= 100)
        {
            y = a;

        }
        else throw Ex(y * a);
    }

};

class OffTheField {
public:
    std::string m_off = "Robot off the field!";

    OffTheField(int vert, int horiz) {
        std::cout << "Position robot vertical -> " << vert << std::endl << "Horizontal ->" << horiz << std::endl;
    }
};

class IllegalCommand {
public:
    std::string m_illegal = "Illegal command";

    IllegalCommand(int vert, int horiz) {
        std::cout << "Position robot vertical -> " << vert << std::endl << "Horizontal ->" << horiz << std::endl;
    }
};

class Robot {
private:
    int size = 10;
    std::vector<std::vector<char>> field;
    const char empty = '_';
    const char robot = 'R';
    int rPosVert = 0;
    int rPosHor = 0;

public:
    Robot() {
        field.resize(size, std::vector<char>(size));
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                field[i][j] = empty;
            }
        }
        field[0][0] = robot;
        SetPosRob(0, 0);
    }

    void SetPosRob(int vert, int horiz) {
        rPosVert = vert;
        rPosHor = horiz;
    }

    void Move(const std::string& input) {
        if (input == "left" || input == "Left") {
            if (rPosHor - 1 < 0) {
                throw OffTheField(rPosVert, rPosHor);
            }
            field[rPosVert][rPosHor] = empty;
            field[rPosVert][rPosHor - 1] = robot;
            SetPosRob(rPosVert, rPosHor - 1);
            print();
        }
        else if (input == "right" || input == "Right") {
            if (rPosHor + 1 > size) {
                throw OffTheField(rPosVert, rPosHor);
            }
            field[rPosVert][rPosHor] = empty;
            field[rPosVert][rPosHor + 1] = robot;
            SetPosRob(rPosVert, rPosHor + 1);
            print();
        }
        else if (input == "top" || input == "Top") {
            if (rPosVert - 1 < 0) {
                throw OffTheField(rPosVert, rPosHor);
            }
            field[rPosVert][rPosHor] = empty;
            field[rPosVert - 1][rPosHor] = robot;
            SetPosRob(rPosVert - 1, rPosHor);
            print();
        }
        else if (input == "down" || input == "Down") {
            if (rPosHor - 1 < 0) {
                throw OffTheField(rPosVert, rPosHor);
            }
            field[rPosVert][rPosHor] = empty;
            field[rPosVert + 1][rPosHor] = robot;
            SetPosRob(rPosVert + 1, rPosHor);
            print();
        }
        else {
            throw IllegalCommand(rPosVert, rPosHor);
        }
    }
    void print() {
        for (int i = 0; i < size; ++i) {
            std::cout << "\n";
            for (int j = 0; j < size; ++j) {
                std::cout << field[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    try {
        std::cout << divide(3, 2) << std::endl;
        std::cout << divide(3.0, 2.0) << std::endl;
        std::cout << divide(1.0, 0.0) << std::endl;
    }
    catch (const DivistionByZero& e) {
        std::cout << e.what() << std::endl;
    }

    Bar b;
    int x;
    while (std::cin >> x && x != 0) {
        try
        {
            b.set(x);
        }
        catch (Ex& err)
        {
            std::cerr << "Exception: ay " << err.x << std::endl;
        }
    }

    std::string move;
    Robot r;
    r.print();
    while (true) {
        try { 
            std::cout << "Enter where to go? (left | right | top | down)" << std::endl;
            std::cin >> move;
            r.Move(move);
        }
        catch (IllegalCommand& error) {
            std::cerr << "Error move : " << error.m_illegal << std::endl;
        }
        catch (OffTheField& error) {
            std::cerr << "Error move : " << error.m_off << std::endl;
        }
    }
    return 0;
}