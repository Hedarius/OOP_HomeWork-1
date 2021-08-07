#include <iostream>
#include <cassert>
#include <vector>
#include <iterator>

class ArrayInt
{
private:
    int m_length;
    int* m_data;

public:
    ArrayInt() : m_length(0), m_data(nullptr)
    { }

    ArrayInt(int length) :
        m_length(length)
    {
        assert(length >= 0);

        if (length > 0)
            m_data = new int[length];
        else
            m_data = nullptr;
    }

    void erase()
    {
        delete[] m_data;

        m_data = nullptr;
        m_length = 0;
    }
    int getLength() { return m_length; }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    void resize(int newLength)
    {
        if (newLength == m_length)
            return;

        if (newLength <= 0)
        {
            erase();
            return;
        }

        int* data = new int[newLength];

        if (m_length > 0)
        {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength;

            for (int index = 0; index < elementsToCopy; ++index)
                data[index] = m_data[index];
        }

        delete[] m_data;

        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index) {
        assert(index >= 0 && index <= m_length);
        int* data = new int[m_length + 1];
        for (int i = 0; i < index; ++i)
            data[i] = m_data[i];
        data[index] = value;
        for (int i = index; i < m_length; ++i)
            data[i + 1] = m_data[i];
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void push_back(int value) {
        insertBefore(value, m_length);
    }

    void pop_back() {
        assert(m_length == 0);
        int* data = new int(m_length - 1);
        for (int i = 0; i < m_length - 1; ++i) {
            data[i] = m_data[i];
        }
        delete[] m_data;
        m_data = data;
        --m_length;
    }

    void pop_front() {
        int* data = new int[m_length - 1];
        for (int i = 0; i < m_length - 1; ++i) {
            data[i] = m_data[i + 1];
        }
        delete[] m_data;
        m_data = data;
        --m_length;
    }

    void print() {
        for (int i = 0; i < m_length; ++i) {
            std::cout << m_data[i] << " ";
        }
    }

    void BubbleSort() {
        int temp;
        for (int i = 0; i < m_length - 1; ++i)
        {
            for (int j = 0; j < m_length - 1; ++j)
            {
                if (m_data[j + 1] < m_data[j])
                {
                    temp = m_data[j + 1];
                    m_data[j + 1] = m_data[j];
                    m_data[j] = temp;
                }
            }
        }
    }

    ~ArrayInt() {
        delete[] m_data;
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
    void Add(Card *newCard) {
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

int main() {
    ArrayInt array;

    for (int i = 0; i < 15; ++i) {
        array.push_back(rand() % 100);
    }

    array.print();

    array.BubbleSort();

    std::cout << std::endl << std::endl;

    array.print();

    return 0;
}