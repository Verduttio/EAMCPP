#include <iostream>
#include <iterator>
#include <regex>

using namespace std;

string getLink(const string& link_string) {
    auto link_start = link_string.substr(link_string.find_first_of('"')+1);
    auto link = link_start.substr(0, link_start.find_first_of('"'));
    return link;
}

string getNameOfLink(const string& link_string) {
    auto name_start = link_string.substr(link_string.find_first_of('>')+1);
    auto name = name_start.substr(0, name_start.find_first_of('<'));
    return name;
}

void findLinks(const string& webpage) {
    auto flags =
            regex_constants::ECMAScript
            | regex_constants::icase
    ;

    regex reg(R"(<a href="https?://[a-zA-Z._/%?=+"]*">[^<]*</a>)", flags);

    auto match_begin = sregex_token_iterator(webpage.begin(), webpage.end(), reg);
    auto match_end = sregex_token_iterator();
    for (auto i = match_begin; i != match_end; i++) {
        cout << getNameOfLink(*i) << " : " << getLink(*i) << endl;
    }
}


void findMails(const string& webpage) {
    auto flags =
            regex_constants::ECMAScript
            | regex_constants::icase
    ;

    regex reg(R"([\s]*[a-zA-Z.-0-9]*@[a-zA-Z-0-9]*[.][a-zA-Z-0-9.]*[\s]*)", flags);
    auto match_begin = sregex_token_iterator(webpage.begin(), webpage.end(), reg);
    auto match_end = sregex_token_iterator();
//    cout << "Matches : " << distance(match_begin, match_end) << endl;
    for (auto i = match_begin; i != match_end; i++) {
        cout << *i << endl;
    }
}


int main(){
    noskipws(cin);  // Do not skip whitespace

    istream_iterator<char> cin_it(cin);
    istream_iterator<char> eos;

    string webpage = string(cin_it, eos);

    cout << "-------Webpage---------\n";
    cout << webpage << endl;

    cout << "Links: \n";
    findLinks(webpage);

    cout << "Mails: \n";
    findMails(webpage);

}