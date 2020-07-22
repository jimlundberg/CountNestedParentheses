// Context: You are given requirements for a utility function that needs to be written in C++. It has the following function signature:
//
//   uint64_t countNestedParentheses(const std::string& str);
//
// The requirements/behavior of the function can be described as:
//
//   Given an arbitrary string of characters, count the maximum level of nested parentheses in the string. Examples:
// 
//   0: ' '
//   1: ( )
//   1: ( ) )
//   2: ( 2 + ( 3 * 4 ) )
//   3: ( ( ( 2 * 2 ) + 1 ) / 8 ) ( )
//
// Tasks:
// 1. Implement the function.
// 2. Define a complete list of tests that need to be written in order to test this function. Just a set of names and descriptions will do.
// 3. Implement at least 2 of these tests.

#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Function to count the number of pairs
uint64_t countNestedParentheses(const std::string& str)
{
    // Create map for open and close tracking
    unordered_map<int, int> open, close;
    int stringLength = str.size();
    int count = 0;

    // Traverse for all bracket sequences 
    for (int i = 0; i < stringLength; i++)
    {
        // Create open and close counters
        int openCount = 0, closeCount = 0;

        if (str[i] == '(')
        {
            // Walk through string
            for (int j = 0; j < stringLength; j++)
            {
                // Check for open brace 
                if (str[j] == '(')
                {
                    openCount++;
                }
                // Else check for closed brace
                else if (str[j] == ')')
                {
                    // Adjust Counts for closed brace
                    if (openCount)
                    {
                        openCount--;
                    }
                    else
                    {
                        closeCount++;
                    }
                }
            }

            // Open and no closing 
            if (openCount && !closeCount)
            {
                open[openCount]++;
            }

            // Close and no open
            if (closeCount && !openCount)
            {
                close[closeCount]++;
            }

            // Neither open or close
            if (!openCount && !closeCount)
            {
                count++;
            }
        }
    }

    // Divide in half to get number of pairs
    // count = count / 2;

    // Check open to find minumum
    for (auto it : open)
    {
        count += std::min(it.second, close[it.first]);
    }

    return count;
}

// Testing code
int main()
{
    vector<string> strings = 
    { 
        " ",
        "( )",
        "( ) )",
        "( 2 + ( 3 * 4 ) )",       
        "( ( ( 2 * 2 ) + 1 ) / 8 ) ( )",
        "( ( ( 2 () * 2 ) + 1 ) / 8 ) ( )"
    };

    int size = strings.size();
    string sentence = "";
    for (int i = 0; i < size; i++)
    {
        sentence = strings[i];
        std::cout << countNestedParentheses(sentence) << " Parentheses found in " << "\"" << sentence << "\"" << std::endl;
    }

    cin.get();
}
