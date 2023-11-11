#include "word_counter.h"
#include <algorithm>

ostream& operator<<(ostream& os, entry const& ent)            //moze byc poza klasa bo korzysta z metod publicznych
{
    return os << "(" << ent.get_value() << ", " <<  ent.get_count() << ")";
}

// static bool lex_lessthan(entry const& left, entry const& right)
// {                                             // static oznacza ze jest dostepne tylko w tym pliku
//     return left.get_value() < right.get_value();
// }

// static bool operator==(entry const& left, string const& val)
// {
//     return left.get_value() == val;
// }

// struct unary_equal       // niepotrzebne bo mamy wyrazenie lambda
// {
//     string val;
//     bool operator()(entry const& left)
//     {
//         return left.get_value() == val;
//     }  
// };

word_counter::freq_iterator::freq_iterator(
    vector<entry>::const_iterator const& cstart,
    vector<entry>::const_iterator const& cstop)
    :start(cstart), stop(cstop)
    {
    auto freq_more = [](entry const& left, entry const& right)
    {
        return left.get_count() < right.get_count();
    };

    auto lex_less = [](entry const& left, entry const& right)
    {
        return left.get_value() < right.get_value();
    };

    current = max_element(start, stop, freq_more);
    current_val = min_element(start, stop, lex_less);
    }
    


word_counter::freq_iterator word_counter::freq_iterator::operator++(int)
{
    auto retv = *this;
    int cur_cnt = current -> get_count();
    string cur_val = current_val -> get_value();

    auto cmp_equal = [cur_cnt](entry const& ent)
    {
        return ent.get_count() == cur_cnt;
    };

    auto cmp_equal_val = [cur_val](entry const& ent)
    {
        return ent.get_value() == cur_val;
    };

    current = find_if(current+1, stop, cmp_equal);
    current_val = find_if(current+1, stop, cmp_equal_val);

    if (current == stop)
    {
        int cur_min = 0;
        for(auto it = start; it != stop; it++)
            if (it->get_count() < cur_cnt && it->get_count() > cur_min)
            {
            cur_min = it->get_count();
            current = it;
            }
    }
    return retv;
}

word_counter::lex_iterator::lex_iterator(
    vector<entry>::const_iterator const& cstart,
    vector<entry>::const_iterator const& cstop)
    : start(cstart), stop(cstop)
{
    auto lex_less = [](entry const& left, entry const& right)    // wyrazenie lambda
    {
        return left.get_value() < right.get_value();
    };
    current = min_element(start, stop, lex_less);       // ma byc maks element dla freq_iterator
    // current = cstop;
    // string cur_min("\255");
    // for(auto it = start; it != stop; it++)
    //     if (it->get_value() < cur_min)
    //     {
    //         cur_min = it->get_value();
    //         current = it;
    //     }
}

word_counter::lex_iterator word_counter::lex_iterator::operator++(int)
{
    auto retv = *this;
    // jak zmienic current?
    string cur_val = current -> get_value();

    // unary_equal compare{cur_val};
    // cout << "\nCompare val: " << compare.val << "\n";
    auto cmp_equal = [cur_val](entry const& ent)
    {
        // cout << "\ncur_val: " << cur_val << "\n";
        return ent.get_value() == cur_val;
    };

    current = find_if(current+1, stop, cmp_equal);
    // for(current++; current!= stop && current->get_value() != cur_val; current++)
    //     ;
    if (current == stop)
    {
        string cur_min("\255");
        for(auto it = start; it != stop; it++)
            if (it->get_value() > cur_val && it->get_value() < cur_min)
            {
                cur_min = it->get_value();
                current = it;
            }
    }
    return retv;
}


void word_counter::add_word(string const& word)
{
    for(size_t idx=0; idx < counter.size(); idx++)
    {
        if (counter[idx].get_value() == word)
        {    
            counter[idx]++;
            return;
        }
    }
    counter.push_back(entry(word, 1));
}

ostream& operator<<(ostream& os, word_counter const& wc)
{
    os << '[';
    // for(size_t idx=0; idx < wc.size(); ++idx)
    //     os << wc.counter[idx];
    // for(vector<entry>::const_iterator it = wc.counter.cbegin();
    //     it != wc.counter.cend();
    //     it++)
    //     os << *it;

    for (auto const& ent : wc.counter)
        os << ent;

    return os << ']';
}
