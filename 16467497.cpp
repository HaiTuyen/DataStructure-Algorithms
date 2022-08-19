#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include<vector>
using namespace std;

// Hash fuction to convert current character into an corresponding index
// Use character from 'a' to 'z' only
#define char_to_int(c) ((int)c - (int)'a')

// Hash fuction to convert current index number into a corresponding character 
// Use number from '0' to '26' only
#define int_to_char(c) ((char)c + (char)'a')

// Numbers of letter in an alphabet
#define SIZE (26)

// Definition of a Trie node
struct TRIENODE
{
    TRIENODE* Child[SIZE];
    // isEndOfWord is true if the node repsents end of a word and vice versa
    bool isEndOfWord;
};

// Fuction to create a Trie node, return a Trie node at the end
TRIENODE* CreateNode()
{
    TRIENODE* newNode = new TRIENODE;
    newNode->isEndOfWord = false;
    // Initialize all child nodes to NULL
    for (int i = 0; i < SIZE; i++)
        newNode->Child[i] = NULL;
    return newNode;
}

// Function to insert a key into a Trie
// If not present, create a new node and inserts key into trie
// If the key is prefix of trie node, just marks the isEndOfWord node
void InsertNode(TRIENODE* root, string Key)
{
    int n = strlen(Key.c_str());
    TRIENODE* p = root;

    for (int i = 0; i < n; i++)
    {
        int index = char_to_int(Key[i]);

        if (p->Child[index] == NULL)
            p->Child[index] = CreateNode();

        p = p->Child[index];
    }
    p->isEndOfWord = true;
}

// Function to copy a hash table into another hash table
void CrawlHash(int copyHash[], int Hash[])
{
    for (int i = 0; i < SIZE; i++)
    {
        copyHash[i] = Hash[i];
    }
}

// A recursive function to find possible valid words present in array
void SearchWord(TRIENODE* root, int Hash[], string str, vector<string>& V)
{
    // If we found a word in Trie, push pack that word into a vector of strings
    if (root->isEndOfWord == true && str.length() >= 3)
        V.push_back(str);

    // Travese all child's of current root
    for (int i = 0; i < SIZE; i++)
    {
        if (Hash[i] != 0 && root->Child[i] != NULL)
        {
            // Add current character
            char c = int_to_char(i);
            // Create a crawl hash table to compute
            int copyHash[SIZE];
            CrawlHash(copyHash, Hash);
            copyHash[i]--;
            // Recursively search reaming character of word in trie
            SearchWord(root->Child[i], copyHash, str + c, V);
        }
    }
}

// Function to find all possible valid words present in array
void FindAllWords(char Arr[], TRIENODE* root, int n, vector<string>& V)
{
    // create a 'hash table' that will store all present characters in Arr[]
    int Hash[SIZE] = { 0 };

    for (int i = 0; i < n; i++)
        Hash[char_to_int(Arr[i])]++;
    
    // Temporary node
    TRIENODE* p = root;

     // string to hold output words
    string str = "";

    // Traverse all matrix elements
    // There are only 26 character possible in char array.
    for (int i = 0; i < SIZE; i++)
    {
        // Start searching for word in dictionary if we found a character which is child
        // of Trie root
        if (Hash[i] != 0 && p->Child[i])
        {
            str = str + (char)int_to_char(i);
            int copyHash[SIZE];
            CrawlHash(copyHash, Hash);
            copyHash[i]--;
            SearchWord(p->Child[i], copyHash, str, V);
            str = "";
        }
    }
}

// Read given dictionary file, then insert all words into a Trie 
void ReadFile(TRIENODE* root, string line_info)
{
    ifstream fi;
    fi.open(line_info.c_str());
    string temp;
    while (!fi.eof())
    {
        getline(fi, temp, '\n');
        InsertNode(root, temp);
    }
    fi.close();
}

// Function to check for valid input
bool checkInputArray(char* a,int count) {
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            // Being sorted ascending in lexicographic order, separated by a single space " "
            // May appear multiple times
            if (a[j] >= a[i]) continue;
            else return false;
        }
        // Being in lowercase, not in capital
        if (a[i] >= 'a' && a[i] <= 'z') continue;
        else return false;
    }
    return true;
}

// Function to check valid input string
bool checkInputString(string s) {
    // All character in range from 'a' to 'z'
    for (int i = 0; i < s.size()-1; i++) {
        if ((s[i] >= 'a' && s[i] <= 'z') && (s[i + 1] >= 'a' && s[i + 1] <= 'z')) return false;
    }
    return true;
}

// Function to read input from user
char* ReadInput(int& count) {
    string a;
    int temp = 0;
    char* c = new char;
    do {
        temp = 0;
        count = 0;
        cout << "input string (lowercase, ascending, separated by a single space): ";
        getline(cin, a);
        if (checkInputString(a) == true) {
            for (int i = 0; i < a.size(); i++) {
                if (a[i] != ' ') {
                    temp++;
                }
            }
            c = new char[temp];
            for (int i = 0; i < a.size(); i++) {
                if (a[i] != ' ') {
                    c[count++] = a[i];
                }
            }
            if (checkInputArray(c, count) == false) {
                cout << "Error input! Please re-enter again!" << endl;
            }
        }
        else  cout << "Error input! Please re-enter again!" << endl;
    } while (checkInputString(a) == false || checkInputArray(c,count) == false);
    return c;
}

// Function to print all words in vector 
void PrintValidWords(vector<string> V)
{
    cout << "-----------------------------------" << endl;
    cout << V.size() << endl;
    for (int i = 0; i < V.size(); i++)
    {
        cout << V[i] << endl;
    }
}


int main()
{
    struct TRIENODE* root = CreateNode();
    vector<string> V;
    ReadFile(root, "Dic.txt");
    int N;
    char* arr = ReadInput(N);
    FindAllWords(arr, root, N, V);
    PrintValidWords(V);
    delete[] arr;
    return 0;
}