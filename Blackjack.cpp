#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

class Card {
public:
    enum CardsValue {
        Ace = 1,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,
        Jack,
        Queen,
        King,
    };

    enum Suits {
        Hearts,
        Diamonds,
        Clubs,
        Spades
    };

    bool cardPosition;

public:
    Card(CardsValue r = Ace, Suits s = Spades, bool fu = true) : m_rank(r), m_suit(s), m_FaceUp(fu) {}

    void Flip() {
        m_FaceUp = !(m_FaceUp);
    }

    int GetValue() const {
        int value = 0;
        if (m_FaceUp) {
            value = m_rank;
            if (value > 10) {
                value = 10;
            }
        }
        return value;
    }

    friend class Hand;
    friend std::ostream& operator<<(std::ostream& os, const Card& aCard);

private:
    CardsValue m_rank;
    Suits m_suit;
    bool m_FaceUp;
};

class Hand {
protected:
    std::vector<Card*> m_handCards;
public:
    Hand() {
        m_handCards.reserve(7);
    }

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

    int GetTotal() const {
        if (m_handCards.empty()) {
            return 0;
        }
        if (m_handCards[0]->GetValue() == 0) {
            return 0;
        }

        int totalVal = 0;

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

    virtual bool isHitting() const = 0;

    bool bustCards() {
        return (GetTotal() > 21);
    }

    void printBust() {
        std::cout << m_name << "busts card" << std::endl;
    }
};

class Player : public GenericPlayer {
public:
    Player(const std::string& name = "") : GenericPlayer(name) {}
    virtual ~Player() {}
    virtual bool isHitting() const {
        std::cout << m_name << " , do you want a hit? (Y/N): ";
        char response;
        std::cin >> response;
        return (response == 'y' || response == 'Y');
    }
    void Win() {
        std::cout << m_name << " wins!" << std::endl;
    }
    void Lose() {
        std::cout << m_name << " loses." << std::endl;
    }
    void Push() {
        std::cout << m_name << " pushes." << std::endl;
    }
};

class House : public GenericPlayer {
public:
    House(const std::string& name = "House") : GenericPlayer(name) {}
    virtual ~House() {}
    virtual bool isHitting() const {
        return (GetTotal() <= 16);
    }
    void FlipFirstCard() {
        if (!(m_handCards.empty())) {
            m_handCards[0]->Flip();
        }
        else {
            std::cout << "No card to flip!\n";
        }
    }
};

class Deck : public Hand {
public:
    Deck() {
        m_handCards.reserve(52);
        Populate();
    }
    ~Deck() {}
    void Populate() {
        Clear();
        for (int s = Card::Hearts; s <= Card::Spades; ++s) {
            for (int r = Card::Ace; r <= Card::King; ++r) {
                Add(new Card(static_cast<Card::CardsValue>(r), static_cast<Card::Suits>(s)));
            }
        }
    }
    void Shuffle() {
        random_shuffle(m_handCards.begin(), m_handCards.end());
    }
    void Deal(Hand& aHand) {
        if (!m_handCards.empty()) {
            aHand.Add(m_handCards.back());
            m_handCards.pop_back();
        }
        else {
            std::cout << "Out of cards. Unable to deal.";
        }
    }
    void AdditionalCards(GenericPlayer& aGenericPlayer) {
        std::cout << std::endl;
        while (!(aGenericPlayer.bustCards()) && aGenericPlayer.isHitting()) {
            Deal(aGenericPlayer);
            std::cout << aGenericPlayer << std::endl;
            if (aGenericPlayer.bustCards()) {
                aGenericPlayer.printBust();
            }
        }
    }
};

class Game {
private:
    Deck m_Deck;
    House m_House;
    std::vector<Player> m_Players;
public:
    Game(const std::vector<std::string>& names) {
        std::vector<std::string>::const_iterator pName;
        for (pName = names.begin(); pName != names.end(); ++pName) {
            m_Players.push_back(Player(*pName));
        }
        srand(static_cast<unsigned int>(time(0)));
        m_Deck.Populate();
        m_Deck.Shuffle();
    }
    ~Game() {}
    void Play() {
        std::vector<Player>::iterator pPlayer;
        for (int i = 0; i < 2; ++i) {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
                m_Deck.Deal(*pPlayer);
            }
            m_Deck.Deal(m_House);
        }
        m_House.FlipFirstCard();
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
            std::cout << *pPlayer << std::endl;
        }
        std::cout << m_House << std::endl;
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
            m_Deck.AdditionalCards(*pPlayer);
        }
        m_House.FlipFirstCard();
        std::cout << std::endl << m_House;
        m_Deck.AdditionalCards(m_House);
        if (m_House.bustCards()) {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
                if (!(pPlayer->bustCards())) {
                    pPlayer->Win();
                }
            }
        }
        else {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
                if (!(pPlayer->bustCards())) {
                    if (pPlayer->GetTotal() > m_House.GetTotal()) {
                        pPlayer->Win();
                    }
                    else if(pPlayer->GetTotal() < m_House.GetTotal()) {
                        pPlayer->Lose();
                    }
                    else {
                        pPlayer->Push();
                    }
                }
            }
        }
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
            pPlayer->Clear();
        }
        m_House.Clear();
    }
};

std::ostream& operator<<(std::ostream& os, const Card& aCard);
std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer);

int main() {
    std::cout << "\t\tWelcome to Blackjack!\n\n";
    int numPlayers = 0;
    while (numPlayers < 1 || numPlayers > 7) {
        std::cout << "How many players? (1-7): ";
        std::cin >> numPlayers;
    }
    std::vector<std::string> names;
    std::string name;
    for (int i = 0; i < numPlayers; ++i) {
        std::cout << "Enter player name: ";
        std::cin >> name;
        names.push_back(name);
    }
    std::cout << std::endl;
    Game aGame(names);
    char again = 'y';
    while (again != 'n' && again != 'N') {
        aGame.Play();
        std::cout << "\nDo you want to play again? (Y/N): ";
        std::cin >> again;
    }
    return 0;
}

std::ostream& operator<<(std::ostream& os, const Card& aCard)
{
    const std::string CardsValue[] = { "O", "Р", "2", "3", "4", "5", "6", "7", "8", "9",
    "10", "J", "Q", "K" };
    const std::string Suits[] = { "C", "D", "H", "S" };
    if (aCard.m_FaceUp)
    {
        os << CardsValue[aCard.m_rank] << Suits[aCard.m_suit];
    }
    else
    {
        os << "ее";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer)
{
    os << aGenericPlayer.m_name << ":\t";
    std::vector<Card*>::const_iterator pCard;
    if (!aGenericPlayer.m_handCards.empty()) {
        for (pCard = aGenericPlayer.m_handCards.begin(); pCard != aGenericPlayer.m_handCards.end(); ++pCard) {
            os << *(*pCard) << "\t";
        }
        if (aGenericPlayer.GetTotal() != 0) {
            std::cout << "(" << aGenericPlayer.GetTotal() << ")";
        }
    }
    else {
        os << "<empty>";
    }
    return os;
}