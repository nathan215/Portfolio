#include <iostream>
#include <climits>
#include <cstdio>

using namespace std;

const int MAX_STRLEN = 1000;
const int NUM_CHARS_PER_LINE = 50;
const int MAX_LINES = 15;

int countCharacters(const char str[]);
int countWords(const char str[]);
int countNumOccurences(const char str[], const char target[]);

void swapString(char str[], const char target[], const char to[]);
void encryptText(char str[], int shift);

void convertIntoLines(const char str[], char lines[MAX_LINES][NUM_CHARS_PER_LINE]);
void printRightJustified(const char str[]);
void printLeftJustified(const char str[]);

void convertStrToPigLatin(char word[]);
void printPigLatin(const char str[]);

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// code starts
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++

// task1
int countCharacters(const char str[])
{
    int characterscount = 0;
    for (int i = 0; str[i] != '\0'; i++)
        characterscount++;
    return characterscount;
}

// task2
int countWords(const char str[])
{
    int wordscount = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (int(str[i]) == 45 || (int(str[i]) >= 65 && int(str[i]) <= 90) || (int(str[i]) >= 97 && int(str[i]) <= 122))
        {
            for (; int(str[i]) == 45 || (int(str[i]) >= 65 && int(str[i]) <= 90) || (int(str[i]) >= 97 && int(str[i]) <= 122); i++);
            wordscount++;
        }
    }
    return wordscount;
}

// task3
void swapString(char str[], const char target[], const char to[])
{
    char neww[1000] = {};
    int newc = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        for (int k = 0; target[k] != '\0'; k++)
        {
            if (str[i + k] != target[k])
            {
                neww[newc + i] = str[i];
                break;
            }
            if (target[k + 1] == '\0')
            {
                int time = 0;
                for (int p = 0; to[p] != '\0'; p++)
                {
                    neww[i + p + newc] = to[p];
                    time++;
                }
                newc = newc + time - k - 1;
                i = i + k;
            }
        }
    }
    int i = 0;
    for (; neww[i] != '\0'; i++)
        str[i] = neww[i];
    str[i] = '\0';
}

//task 4
void encryptText(char str[], int shift)
{
    while (shift < 0)
        shift = shift + 26;
    shift = shift % 26;
    for (int i = 0; str[i] != '\0'; i++)
    {
        int change = str[i];
        if (change >= 'a' && change <= 'z')
        {
            change = change + shift;
            if (change > 'z')
                change = change - 'z' + 'a' - 1;
            str[i] = change;
        }
        else if (change >= 'A' && change <= 'Z')
        {
            change = change + shift;
            if (change > 'Z')
                change = change - 'Z' + 'A' - 1;
            str[i] = change;
        }
    }
}

// task5
int countNumOccurences(const char str[], const char target[])
{
    int countnumber = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        for (int k = 0; target[k] != '\0'; k++)
        {
            if (str[i + k] != target[k])
            {
                countnumber--;
                break;
            }
            if (target[k + 1] == '\0')
                i = i + k;
        }
        countnumber++;
    }
    return countnumber;
}

bool isWordChar(char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c == '-');
}

// task6
void convertIntoLines(const char str[], char lines[MAX_LINES][NUM_CHARS_PER_LINE])
{
    for (int i = 0; i < MAX_LINES; ++i)
    {
        lines[i][0] = '\0';
    }

    int strLen = countCharacters(str);
    int line = 0;
    int tail = 0;
    int i = 0;

    while (i < strLen)
    {
        if (isWordChar(str[i]))
        {
            int wordLen = 1;
            while (i + wordLen < strLen && isWordChar(str[i + wordLen]))
                ++wordLen;

            if (wordLen + tail < NUM_CHARS_PER_LINE)
            {
                for (int j = 0; j < wordLen; ++j)
                    lines[line][tail++] = str[i + j];
                i += wordLen;
            }
            else
            {
                lines[line++][tail] = '\0';
                tail = 0;
            }
        }
        else
        {
            if (tail == 0 && str[i] == ' ')
            {
                i++;
                continue;
            }
            lines[line][tail++] = str[i++];
        }
        if (tail == NUM_CHARS_PER_LINE - 1)
        {
            lines[line++][tail] = '\0';
            tail = 0;
        }
    }
    lines[line][tail] = '\0';

    for (int line = 0; line < MAX_LINES && lines[line][0] != '\0'; ++line)
    {
        int last = 0;
        for (int i = 0; lines[line][i] != '\0'; ++i)
            last = (lines[line][i] != ' ') ? i : last;
        lines[line][last + 1] = '\0';
    }
}

void printLeftJustified(const char str[])
{
    char lines[MAX_LINES][NUM_CHARS_PER_LINE];
    convertIntoLines(str, lines);

    for (int i = 0; i < MAX_LINES && lines[i][0] != '\0'; ++i)
    {
        cout << lines[i] << endl;
    }
}

void printRightJustified(const char str[])
{
    char lines[MAX_LINES][NUM_CHARS_PER_LINE];
    convertIntoLines(str, lines);

    for (int line = 0; line < MAX_LINES && lines[line][0] != '\0'; ++line)
    {
        for (int i = NUM_CHARS_PER_LINE - countCharacters(lines[line]) - 1; i > 0; --i)
            cout << ' ';
        cout << lines[line] << endl;
    }
}

// task7
void printJustified(const char str[])
{
    char lines[MAX_LINES][NUM_CHARS_PER_LINE];
    convertIntoLines(str, lines);

    int nLines = 0;
    while (nLines < MAX_LINES && lines[nLines][0] != '\0')
        ++nLines;

    for (int line = 0; line < nLines - 1; ++line)
    {
        int len = countCharacters(lines[line]);
        int extra = NUM_CHARS_PER_LINE - len - 1;
        int nSpaces = 0;
        bool space = false;
        for (int i = 0; i < len; ++i)
        {
            if (!space && lines[line][i] == ' ')
                space = true;
            else if (space && lines[line][i] != ' ')
            {
                space = false;
                ++nSpaces;
            }
        }
        nSpaces += space;

        int cur = 0;
        space = false;
        for (int i = 0; i < len; ++i)
        {
            if (lines[line][i] == ' ' && !space)
            {
                int j = (extra / nSpaces) + ((cur < extra % nSpaces) ? 1 : 0);
                for (; j > 0; --j)
                {
                    cout << ' ';
                }
                cout << ' ';
                space = true;
                ++cur;
            }
            else
            {
                if (lines[line][i] != ' ' && space)
                    space = false;
                cout << lines[line][i];
            }
        }
        cout << endl;
    }

    if (nLines > 0)
        cout << lines[nLines - 1] << endl;
}

// task8
void convertStrToPigLatin(char str[])
{
    char word[MAX_STRLEN][NUM_CHARS_PER_LINE];
    int num = 0;
    int line = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {

        if ((int(str[i]) >= 65 && int(str[i]) <= 90) || (int(str[i]) >= 97 && int(str[i]) <= 122) || int(str[i]) == 45)
        {
            word[line][num] = str[i];
            num++;
            if (str[i + 1] == '\0')
            {
                word[line][num] = '\0';
                line++;
                break;
            }
        }
        else
        {
            word[line][num] = '\0';

            line++;
            num = 0;
            for (; (int(str[i]) < 65 && int(str[i]) != 45) || (int(str[i]) > 90 && int(str[i]) < 97) || int(str[i]) > 122; i++)
            {
                word[line][num] = str[i];
                num++;
                if (str[i] == '\0')
                {
                    line++;
                    break;
                }
            }

            i--;
            word[line][num] = '\0';
            line++;
            num = 0;
        }
    }
    word[line][0] = '\0';

    for (int i = 0; word[i][0] != '\0'; i++)
    {
        if (word[i][0] == 'a' || word[i][0] == 'e' || word[i][0] == 'i' || word[i][0] == 'o' || word[i][0] == 'u' ||
            word[i][0] == 'A' || word[i][0] == 'E' || word[i][0] == 'I' || word[i][0] == 'O' || word[i][0] == 'U')
        {
            int j = 0;
            for (; word[i][j] != '\0'; j++)
                ;
            word[i][j] = 'y';
            word[i][j + 1] = 'a';
            word[i][j + 2] = 'y';
            word[i][j + 3] = '\0';
        }
        else if (word[i][0] == ' ' || word[i][0] == ',' || word[i][0] == '.')
        {
            continue;
        }
        else
        {
            char keep[NUM_CHARS_PER_LINE * 2] = {};
            int k = 0;
            for (; word[i][k] != '\0'; k++)
                ;
            int j = 0;
            int j_keep = 0;
            for (; word[i][j] != '\0'; j++)
            {
                if (word[i][j] == 'a' || word[i][j] == 'e' || word[i][j] == 'i' || word[i][j] == 'o' || word[i][j] == 'u' ||
                    word[i][j] == 'A' || word[i][j] == 'E' || word[i][j] == 'I' || word[i][j] == 'O' || word[i][j] == 'U')
                {
                    j_keep = j;
                    for (; word[i][j] != '\0'; j++)
                    {
                        keep[j] = word[i][j];
                    }
                    keep[k] = 'a';
                    keep[k + 1] = 'y';
                    keep[k + 2] = '\0';

                    break;
                }
                else
                {
                    keep[k] = word[i][j];
                    k++;
                }
            }
            int q = 0;
            for (int g = j_keep; keep[g] != '\0'; g++, q++)
            {
                word[i][q] = keep[g];
            }
            word[i][q] = '\0';
        }
    }
    int worr = 0;
    for (int i = 0; word[i][0] != '\0'; i++)
    {
        for (int k = 0; word[i][k] != '\0'; k++)
        {
            str[worr] = word[i][k];
            worr++;
        }
    }
    str[worr] = '\0';
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++

// ++++++++++++++++++++++++++++++++++++++++++++++++++++

void printPigLatin(const char str[])
{
    char pigLatin[MAX_STRLEN];
    for (int i = 0; i < MAX_STRLEN; ++i)
    {
        pigLatin[i] = str[i];
    }
    convertStrToPigLatin(pigLatin);
    int strLen = countCharacters(pigLatin);
    for (int i = 0; i < strLen; ++i)
    {
        if (pigLatin[i] >= 'A' && pigLatin[i] <= 'Z')
        {
            pigLatin[i] = 'a' + pigLatin[i] - 'A';
        }
    }
    cout << pigLatin << endl;
}

void printMainDisplay(const char str[])
{
    cout << str << endl
         << "===================================\n"
         << "1. Character Count\n"
         << "2. Word Count\n"
         << "3. Encrypt (Caeser Cipher)\n"
         << "4. Find and Replace String Globally\n"
         << "5. Find Frequency of String\n"
         << "6. Print Left Align Text\n"
         << "7. Print Right Align Text\n"
         << "8. Print Left-Right Align Text\n"
         << "9. Print Pig Latin\n"
         << "Please make your choice: ";
}

int main()
{
    int choice = 0;
    char str[MAX_STRLEN];

    cout << "Enter text: ";
    cin.getline(str, MAX_STRLEN, '\n');

    do
    {
        printMainDisplay(str);
        cin >> choice;
    } while (choice < 1 || choice > 9);

    if (choice == 1)
    {
        cout << "Total character count: " << countCharacters(str) << endl;
    }
    else if (choice == 2)
    {
        cout << "Total word count: " << countWords(str) << endl;
    }
    else if (choice == 3)
    {
        cout << "Enter the shift amount for the caeser cipher encryption (rotation encryption): ";
        int shift;
        cin >> shift;
        encryptText(str, shift);
        cout << str << endl;
    }
    else if (choice == 4)
    {
        cout << "Enter the string to find and replace: ";
        char target[MAX_STRLEN];
        cin.ignore(INT_MAX, '\n');
        cin.getline(target, MAX_STRLEN, '\n');

        cout << "Enter the string to replace it with: ";
        char to[MAX_STRLEN];
        cin.getline(to, MAX_STRLEN, '\n');

        swapString(str, target, to);
        cout << str << endl;
    }
    else if (choice == 5)
    {
        cout << "Enter the string to count the occurences of: ";
        char target[MAX_STRLEN];
        cin.ignore(INT_MAX, '\n');
        cin.getline(target, MAX_STRLEN, '\n');

        cout << '"' << target << '"' << " appears in the text " << countNumOccurences(str, target) << " time(s).\n";
    }
    else if (choice == 6)
    {
        printLeftJustified(str);
    }
    else if (choice == 7)
    {
        printRightJustified(str);
    }
    else if (choice == 8)
    {
        printJustified(str);
    }
    else if (choice == 9)
    {
        printPigLatin(str);
    }
}


