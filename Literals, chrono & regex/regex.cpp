#include <iostream>
#include <regex>

using namespace std;

std::string s = "To be, or not to be, that is the question,\n"
                "Whether 'tis nobler in the mind to suffer\n"
                "The slings and arrows of outrageous fortune,\n"
                "Or to take arms against a sea of troubles,\n"
                "And by opposing end them? To die: to sleep;";

void basicRegex() {
    auto flags =
            regex_constants::ECMAScript
            | regex_constants::icase
            //| regex_constants::multiline
    ;
    regex reg("to (.*),", flags);

    smatch match;

    if(regex_search(s, match, reg)){
        cout << "Prematch  : " << match.prefix() << endl;
        for(int i =0; i<match.size(); i++){
            cout << i << " : " << match[i] << endl;
        }
       cout << "Postmatch  : " << match.suffix() << endl;
    }
//    string s2 = match.suffix();
//    if(regex_search(s2, match, reg)){
//        cout << "Prematch  : " << match.prefix() << endl;
//        for(int i =0; i<match.size(); i++){
//            cout << i << " : " << match[i] << endl;
//        }
//        cout << "Postmatch  : " << match.suffix() << endl;
//    }
}

void regexIterator(){
    auto flags = regex_constants::ECMAScript;

   // [acdTr]
   // \w   [a-zA-Z_]
   // \W   ^[a-zA-Z_]
   // \d   digit
   // \s   white space
   //  \w+    1,2,...
   // \w*     0,1,2,...
   // \w{2}   2
   // \w{2,}  2,3,4
   // \w{3,5}  3,4,5
   //
   //regex reg("to (\\w+)\\W+(\\w+)", flags);

   regex reg(R"(to (\w+)\W+(\w+))", flags);


//    {
//        auto match_begin = sregex_iterator(s.begin(), s.end(), reg);
//        auto match_end = sregex_iterator();
//        cout << "Matches : " << distance(match_begin, match_end) << endl;
//        for (auto i = match_begin; i != match_end; i++) {
//            smatch match = *i;
//            cout << match[1]<< " " << match[2] << endl;
//        }
//    }
    {
        auto match_begin = sregex_token_iterator(s.begin(), s.end(), reg);
        auto match_end = sregex_token_iterator();
        cout << "Matches : " << distance(match_begin, match_end) << endl;
        for (auto i = match_begin; i != match_end; i++) {
            cout << *i << endl;
        }
    }
}


int main(){
//    basicRegex();
    regexIterator();
    return 0;

}