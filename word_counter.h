#pragma once
#include <iostream>
#include <vector>

using namespace std;

class entry
{
    string value;
    int count = 0;

    public:
        entry(string const& val, int const& cnt = 1) : value(val), count(cnt)
        {}
        string const& get_value() const     //zwracam referencje na wartosc ktora jest stala
        {
            // return entry::value;
            // return this->value;
            return value;
        }
        int get_count() const        //nie dajemy ampersanda bo const na int to wiekszy koszt niz zwrocenie samej wartosci
        {
            return count;
        }

        int operator++(int)     // operator jest tylko po to aby rozroznic przeciazony operator od zwyklego operatora ++
        {
            return count++;     // metoda moglaby rowniez byc voidem
        }
};

ostream& operator<<(ostream& os, entry const& ent);

class word_counter
{
    private:
        vector<entry> counter;            // nie trzeba pisac destruktora bo w klasie string i vector juz jest destruktor
    
    public:
        class freq_iterator
        {
            vector<entry>::const_iterator current;
            vector<entry>::const_iterator current_val;
            vector<entry>::const_iterator start;
            vector<entry>::const_iterator stop;
            public:
                freq_iterator(vector<entry>::const_iterator const& cstart,
                    vector<entry>::const_iterator const& cstop);
                
                entry const& operator*() const
                {
                    return *current;
                }
                freq_iterator operator++(int);
                bool operator==(freq_iterator const& other) const
                {
                    return current == other.current;
                }
                bool operator!=(freq_iterator const& other) const
                {
                    return !operator==(other);
                }
        };

        class lex_iterator
        {
            vector<entry>::const_iterator current;
            vector<entry>::const_iterator start;
            vector<entry>::const_iterator stop;
            public:
                lex_iterator(vector<entry>::const_iterator const& cstart,
                    vector<entry>::const_iterator const& cstop);     //konstruktor
                entry const& operator*() const      //przy kazdej operacji bylaby kopia obiektu entry [BEZ CONST&], drugi const bo obiekt sie nie zmienia
                {
                    return *current;
                }
                lex_iterator operator++(int);                // post inkrementacja tylko gdy argument int
                bool operator==(lex_iterator const& other) const     //operator porownania
                {
                    return current == other.current;
                }
                bool operator!=(lex_iterator const& other) const      //drugi operator porownania
                {
                    return !operator==(other);
                    // return not this->operator==(other);
                    // return not (*this == other);
                }

        };

        lex_iterator lex_begin() const
        {
            return lex_iterator(counter.cbegin(), counter.cend());
        }
        lex_iterator lex_end() const
        {
            return lex_iterator(counter.cend(), counter.cend());
        }

        freq_iterator freq_begin() const
        {
            return freq_iterator(counter.cbegin(), counter.cend());
        }
        freq_iterator freq_end() const
        {
            return freq_iterator(counter.cend(), counter.cend());
        }


        entry & operator[](string const& word)
        {
        for(size_t i=0; i<this->size(); i++)
            {
            if (counter[i].get_value() == word)
                return counter[i];
            }
        throw "No word in counter";
        }

        word_counter & operator+=(const word_counter &wc)
        {
        for (size_t i=0; i < wc.size(); i++)
            {
            for(int j=0; j<wc.counter[i].get_count(); j++)
                this->add_word(wc.counter[i].get_value());
            }
            return *this;
        }
        
        void add_word(string const& word);      //pzez ustaloną referencję
        // funkcja jest dluga wiec jest w cpp

        size_t size() const
        {
            return counter.size();
        }
        friend ostream& operator<<(ostream& os, word_counter const& wc);
};