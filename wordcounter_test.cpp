#include "word_counter.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    entry ent("Yossarian");
    if (ent.get_count() != 1 || ent.get_value() != "Yossarian")
        cerr << "Invalid values after entry ctor\n";

    stringstream tstream;
    tstream << ent;
    if (tstream.str() != "(Yossarian, 1)")       // metoda str
    {
            cerr << "Invalid content of stream after << --> ";
            cerr << tstream.str() << "\n";
    }

    word_counter wc;
    wc.add_word("yossarian");
    if (wc.size() != 1)
        cerr << "Invalid wc size after the first add_word\n";

    wc.add_word("yossarian");
    wc.add_word("dunbar");
    wc.add_word("clevinger");
    wc.add_word("scheisskopf");
    wc.add_word("scheisskopf");
    wc.add_word("scheisskopf");
    wc.add_word("minderbinder");
    wc.add_word("daneeka");
    cerr << wc << endl;
    vector<string> expected_val {"clevinger", "daneeka", "dunbar", "minderbinder", "scheisskopf", "yossarian"};
    vector<string> expected_cnt {"scheisskopf", "yossarian","dunbar", "clevinger", "minderbinder",  "daneeka" };

    auto lex_it = wc.lex_begin();
    auto exp_val = expected_val.cbegin();
    cerr << "Alphabetical order" << endl;
    cout << "[";
    while (lex_it != wc.lex_end())
    {
    cout << *lex_it;
        if ((*lex_it).get_value() != *exp_val)
        {
            cerr << "]\nInvalid element in alphabetical order " << (*lex_it).get_value() << " instead of " << *exp_val << "\n";
            return 1;
        }
        lex_it++;
        exp_val++;
    }
    cout << "]\n";
    cout << "Test passed\n\n";

    auto freq_it = wc.freq_begin();
    auto exp_cnt = expected_cnt.cbegin();
    cerr << "Numerical order" << endl;
    cout << "[";
    while (freq_it != wc.freq_end())
    {
    cout << *freq_it;
        if ((*freq_it).get_value() != *exp_cnt)
        {
            cerr << "]\nInvalid element in numerical order " << (*freq_it).get_value() << " instead of " << *exp_cnt << "\n";
            return 2;
        }
        freq_it++;
        exp_cnt++;
    }
    cout << "]" << endl;
    cout << "Test passed\n\n";

    cerr <<"Operator[] test"<<"\n";
    string word("daneeka");
    string exp_tuple = "(daneeka, 1)";
    stringstream ret;
    ret << wc[word];
    if (ret.str() != exp_tuple)
        cout << "Operator[] returns undesired result\n";
    else cout << "Test passed\n\n";

    cerr<<wc[word];
    cerr<<"\n\n";

    word_counter wc2;
    wc2.add_word("clevinger");
    wc2.add_word("clevinger");
    wc2.add_word("clevinger");
    wc2.add_word("scheisskopf");
    wc2.add_word("yossarian");
    wc2.add_word("yossarian");
    
    cerr <<"Adding counters"<<"\n";
    cerr <<"First counter"<<"\n";
    for(auto it=wc.freq_begin(); it != wc.freq_end(); it++)
        cerr << *it;
    cerr<<"\n";
    cerr <<"Second counter"<<"\n";
    for(auto it=wc2.freq_begin(); it != wc2.freq_end(); it++)
        cerr << *it;
    cerr<<"\n";

    wc += wc2;
    cerr <<"Adding counters result"<<"\n";
    for(auto it=wc.freq_begin(); it != wc.freq_end(); it++)
        cerr << *it;
    cerr<<"\n";

    cerr << "\nEnd of tests\n";

/* na final: wiekszy tekst do obrobki
    std::ifstream is("TheVoyageoftheBeagle.txt");
    if (!is.good())
    {
        std::cout << "Smuteczek :(\n";
        return -1;
    }

    high_resolution_clock::time_point start = high_resolution_clock::now();
    word_counter wc;

    std::string word;
    while (is >> word)
        wc.add_word(word);   // albo: wc[word]++;

    high_resolution_clock::time_point now = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(now - start);
    std::cout << "Counting in " << time_span.count() << " seconds.\n";

    int limit = 20;

    // alfabetycznie
    std::cout << "\n\nThe Voyage of Beagle by Charles Darwin first 20 words alphabetically\n\n";
    auto lex_iter = wc.lex_begin();
    for (int cnt = 0; cnt < limit; ++cnt)
        std::cout << *lex_iter++ << '\n';

    // po czestosci wystapien
    std::cout << "\n\nThe Voyage of Beagle by Charles Darwin most frequent words\n\n";
    auto freq_iter = wc.freq_begin();
    for (int cnt = 0; cnt < limit; ++cnt)
        std::cout << *freq_iter++ << '\n';
 */
    return 0;
}
