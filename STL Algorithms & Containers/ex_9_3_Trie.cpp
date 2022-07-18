#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;
/**
 * Trie structure
 *
 * HINT: use std::map to implement it!
 *       My implementation adds less than 25 lines of code. 
 */
class Trie{
  /// TODO:
  map<string, Trie> data; //better
public:
    static void printSentence(const std::vector<std::string>  & sentence ){
        for(const auto & w : sentence)
            cout << w << " ";
    }
    void add(const std::vector<std::string>  & sentence ){
       cout << "Adding : ";
       printSentence(sentence);
       cout << "\n";
        /// TODO:
        auto tmp = this;
        for(const auto& w : sentence) {
            tmp = &(tmp->data[w]);
            // tmp now points to newly created Trie
            // and in next iteration program will add another word to this new Trie
        }
    }



    void printPossibleEndings(const std::vector<std::string>  & beginningOfSentence ){
        cout << "Endings for \"";
        printSentence(beginningOfSentence);
        cout << "\" are :\n";
        // TODO:
        // getting the beginning of possible endings
        auto root = this;
        for(const auto& w : beginningOfSentence) {
            root = &(root->data[w]);
        }

        printEndings(root, "");
        cout << endl;
    }

    void load(const std::string & fileName){
        ifstream file(fileName);
        if(!file){
            cerr << "Error when openning file " << fileName << endl;
            return;
        }
        string word;
        vector<string> sentence;
        while( file >> word) {
            sentence.push_back(word);
            // is it end of the sentence?
            if(word.find_last_of('.') != string::npos) {
                add(sentence);
                sentence.clear();
            }
        }
    }

private:
    void printEndings(Trie* trie, const string& ending) {
        if(trie->data.empty())
            cout << "> " << ending << endl;
        else {
            for (auto &it: trie->data) {
                printEndings(&it.second, ending + it.first + " ");
            }
        }
    }
};


int main(){
    Trie dictionary;
    dictionary.load("sample.txt");
//    dictionary.load("hamletEN.txt");

//    dictionary.printPossibleEndings({"First"});
    dictionary.printPossibleEndings({"Curiosity"});
    dictionary.printPossibleEndings({"Curiosity", "killed"});
    dictionary.printPossibleEndings({"The", "mouse","was","killed"});

    /* cout << "Beginning of sentence (ended with single .): ";
    string word;
    vector<string> sentence;
    while(true){
        cin >> word;
        if(word == ".")
            break;
        sentence.push_back(word);
        dictionary.printPossibleEndings(sentence);
    }*/
    return 0;
}
/* Expected output:
Adding : Curiosity killed the cat.
Adding : Curiosity killed the mouse.
Adding : Curiosity saved the cat.
Adding : Curiosity killed the cat and the mouse.
Adding : The cat was killed by curiosity.
Adding : The mouse was killed by cat.
Adding : The mouse was killed by curiosity.
Endings for "Curiosity " are :
 > killed the cat.
 > killed the mouse.
 > killed the cat and the mouse.
 > saved the cat.

Endings for "Curiosity killed " are :
 > killed the cat.
 > killed the mouse.
 > killed the cat and the mouse.

Endings for "The mouse was killed " are :
 > by cat.
 > by curiosity.

 */