// Include standard C++ libraries
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int, int> pii;

// int N = 1000000000; // 1000000000; // number of iterations // 308915776
// int N = 10000000000; // Define number of games to simulate
int N = 1000000000;
int B = 5000000; // Define how many simulations will be run between printing debugging information (see line 46)

// Define strings that will be used/checked against
string alphabet = "abcdefghijklmnopqrstuvwxyz";
string vowels = "aeiou";
string cons = "bcdfghjklmnpqrstvwxyz";

// Function for randomly generating a 6 character word
string genWord()
{
    string word = "";           // Initialise an empty string
    for (int i = 0; i < 6; i++) // Loop 6 times, for each letter
    {
        int r = rand() % 26; // Select a random number between 0 and 25
        word += alphabet[r]; // Select the chosen number from the letters array and append it to the word
    }
    return word;
}

signed main(void)
{
    // Makes program run faster
    ios::sync_with_stdio(false);
    cin.tie(nullptr); //

    srand(time(0)); // Seed the random number generator with current time

    // Initialise variables for recording counts for each prize respectively
    int one = 0;
    int two = 0;
    int three = 0;
    int four = 0;

    // Iterate for the amount of previously defined number of simulations
    for (int i = 0; i < N; i++)
    {
        string word = genWord(); // Call the genWord function to generate and assign a random word

        // For debugging, output the current word and counts for each prize in intervals as defined
        if (i % B == 0 && i > 0)
        {
            cout << i << " " << word << "\n";
            cout << (double)one / (i + 1) << "\n";
            cout << (double)two / (i + 1) << "\n";
            cout << (double)three / (i + 1) << "\n";
            cout << (double)four / (i + 1) << "\n";
            cout << "----------------" << endl;
        }

        // Prize 1: Word must contain "iwin"
        if (word.find("iwin") != string::npos) // Check if the word includes "iwin"
        {
            one++; // Increment count for prize one by 1
            continue;
        }

        int charCounts[26] = {0}; // Initialise an empty size 26 array to track how many times each character appears
        bool palindrome = true;   // A flag used to see if the current word is a palindrome

        // Iterate through each character of the word and increase respective character count by 1
        for (char c : word)
        {
            charCounts[c - 'a']++;
        }

        int oddCount = 0;
        for (int j = 0; j < 26; j++)
        {
            if (charCounts[j] % 2 != 0)
            {
                oddCount++;
            }
        }
        palindrome = (oddCount <= 1);

        // Prize 2: Word must be able to form a palindrome
        if (palindrome) // Check if palindrome flag is true, meaning that the current word is a palindrome
        {
            two++; // Increment count for prize two by 1
            continue;
        }

        // Prize 3: First character must be a vowel & last must be a consonant
        // Check if the first character is in the vowels array and the last character is in the consonants array
        if (vowels.find(word[0]) != string::npos && cons.find(word[5]) != string::npos)
        {
            three++; // Increment count for prize three by 1
            continue;
        }

        int rep = 0;
        int ones = 0;
        for (int j = 0; j < 26; j++)
        {
            if (charCounts[j] == 2)
            {
                rep++;
            }
            else if (charCounts[j] == 1)
            {
                ones++;
            }
        }

        // Prize 4: Exactly one repeat
        // Check if there is exactly 1 repeating letter
        if (rep == 1 && ones == 4)
        {
            four++; // Increment count for prize four by 1
            continue;
        }
    }

    // After running all simulations, output the final counts and probabilities for the prizes:
    cout << "------" << "\n";
    cout << (double)one / N << "\n";
    cout << (double)two / N << "\n";
    cout << (double)three / N << "\n";
    cout << (double)four / N << "\n";
    cout << "------" << "\n";
    cout << one << "\n";
    cout << two << "\n";
    cout << three << "\n";
    cout << four << "\n";
    cout << "----------------" << "\n";

    // House Edge Calculation:

    int C = 5; // Cost to play

    double p1 = (double)one / N;
    double p2 = (double)two / N;
    double p3 = (double)three / N;
    double p4 = (double)four / N;

    double r1 = 161841;
    double r2 = 1346;
    double r3 = 6.85;
    double r4 = 3.26;

    double expectedPayout = p1 * r1 + p2 * r2 + p3 * r3 + p4 * r4;

    double he = ((C - expectedPayout) / C) * 100;

    cout << "House edge: " << he << "%" << endl;

    return 0;
}
