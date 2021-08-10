#include <iostream>
#include <string>
#include <vector>
#include <fstream>

template <class T>

class Pair1 {
private:
	T m_first;
	T m_second;

public:
	Pair1(const T first, const T second)
		: m_first(first), m_second(second) {
	}

	T first() { return m_first; }
	const T first() const { return m_first; }
	T second() { return m_second; }
	const T second() const { return m_second; }
};

template <class T, class S>
class Pair
{
private:
	T m_a;
	S m_b;

public:
	Pair(const T a, const S b)
		: m_a(a), m_b(b)
	{
	}

	T a() { return m_a; }
	const T a() const { return m_a; }
	S b() { return m_b; }
	const S b() const { returpon m_b; }
};

template <class S>

class StringValuePair : public Pair<std::string, S> {
public:
	StringValuePair(const std::string word, const S num)
		: Pair<std::string, S>(word, num) {
	}
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

    friend class Hand;

};

class Hand {
protected:
    std::vector<Card*> m_handCards;
public:
    void Add(Card* newCard) {
        m_handCards.push_back(newCard);
    };

    virtual ~Hand() {
        Clear();
    };

    void Clear() {
        std::vector<Card*>::iterator iter = m_handCards.begin();
        for (iter = m_handCards.begin(); iter != m_handCards.end(); ++iter) {
            delete* iter;
        }
        m_handCards.clear();
    }

    int GetTotal() {
        int totalVal;

        std::vector<Card*>::const_iterator iter;
        for (iter = m_handCards.begin(); iter != m_handCards.end(); ++iter) {
            totalVal += (*iter)->GetValue();
        }

        bool aceInHand = false;

        for (iter = m_handCards.begin(); iter != m_handCards.end(); ++iter) {
            if ((*iter)->GetValue() == Card::Ace) {
                aceInHand = true;
            }
        }
        if (aceInHand && totalVal <= 11) {
            totalVal += 10;
        }
        return totalVal;
    }
};

class GenericPlayer : public Hand {
    friend std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer);

protected:
    std::string m_name;

public:
    GenericPlayer(const std::string& name = "") : m_name(name) {
    }

    virtual ~GenericPlayer() {
    }

    virtual bool takesACard() const = 0;

    bool bustCards() {
        return (GetTotal() > 21);
    }

    void printBust() {
        std::cout << m_name << "busts card" << std::endl;
    }
};

int main() {
	Pair1<int> p1(6, 9);
	std::cout << "Pair: " << p1.first() << " " << p1.second() << std::endl;

	const Pair1<double> p2(3.4, 7.8);
	std::cout << "Pair: " << p2.first() << " " << p2.second() << std::endl;

	std::cout << std::endl << std::endl;

	Pair<int, double> p3(6, 7.8);
	std::cout << "Pair: " << p3.a() << ' ' << p3.b() << std::endl;

	const Pair<double, int> p4(3.4, 5);
	std::cout << "Pair: " << p4.a() << ' ' << p4.b() << std::endl;

	std::cout << std::endl << std::endl;

	StringValuePair<int> svp("Amazing", 7);
	std::cout << "Pair: " << svp.a() << ' ' << svp.b() << std::endl;

	return 0;
}