#include <set>

#include "lvt.hpp"

using namespace lvt;

bool lvt::checkings::is_vowel(char __ch)
{
    return (__ch == 'a' || __ch == 'e' || __ch == 'i' || __ch == 'o' ||
            __ch == 'u' || __ch == 'A' || __ch == 'E' ||
            __ch == 'I' || __ch == 'O' || __ch == 'U')
               ? true
               : false;
}

bool lvt::checkings::isBracketSequenceValid(std::string_view seq)
{
    // Check boundary condition
    if (seq.empty())
        return false;

    // Storing brackets in the stack adapter
    std::stack<char> brackets;
    for (char ch : seq)
    {
        // Pushing back opening bracket
        if (ch == '(' || ch == '[' || ch == '{')
            brackets.push(ch);
        // Pushing back closing bracket
        else
        {
            // If stack is empty
            if (brackets.empty())
                return false;

            // Storing the top element from the stack
            char top{brackets.top()};

            // If we have enclosing brackets (pair of opening and closing bracket)
            // -> erase top element from the stack
            if ((top == '(' && ch == ')') || (top == '[' && ch == ']') || (top == '{' && ch == '}'))
                brackets.pop();
            // Else there is no enclosing pair -> balance is broken
            else
                return false;
        }
    }

    // If stack is empty - all is OK, otherwise - balance is broken
    return brackets.empty();
}

std::string string::modifying::str_to_lower(const std::string &__str)
{
    std::string str{__str};
    std::transform(std::begin(str), std::end(str), std::begin(str), ::tolower);
    return str;
}

std::string string::modifying::str_to_upper(const std::string &__str)
{
    std::string str{__str};
    std::transform(std::begin(str), std::end(str), std::begin(str), ::toupper);
    return str;
}

std::string string::modifying::remove_vowels(const std::string &__str)
{
    std::string str(__str);
    str.erase(std::remove_if(std::begin(str), std::end(str), [](char ch)
                             { return lvt::checkings::is_vowel(ch); }),
              std::cend(str));
    return str;
}

std::string string::modifying::remove_vowels_cxx_20(const std::string &__str)
{
    std::string str(__str);
    std::erase_if(str, [](char ch)
                  { return lvt::checkings::is_vowel(ch); });
    return str;
}

std::string string::modifying::remove_vowels_regex(const std::string &__str)
{
    std::string str(__str);
    std::regex vowels("[aeiouAEOIOU]");
    return std::regex_replace(str, vowels, "");
}

void string::modifying::remove_vowels(std::string &__str)
{
    __str.erase(std::remove_if(std::begin(__str), std::end(__str), [](char ch)
                               { return lvt::checkings::is_vowel(ch); }),
                std::cend(__str));
}

void string::modifying::remove_vowels_cxx_20(std::string &__str)
{
    std::erase_if(__str, [](char ch)
                  { return lvt::checkings::is_vowel(ch); });
}

void string::modifying::remove_vowels_regex(std::string &__str)
{
    std::regex vowels("[aeiouAEOIOU]");
    std::regex_replace(__str, vowels, "");
}

std::string string::modifying::remove_consecutive_spaces(const std::string &__str)
{
    std::string str(__str);

    for (auto it{std::cbegin(str)}; it != std::cend(str); ++it)
    {
        while (((it + 1) != std::cend(str)) && (*it == *(it + 1) && (*it == ' ')))
            str.erase(it);
    }

    return str;
}

void string::modifying::remove_consecutive_spaces(std::string &__str)
{
    for (auto it{std::cbegin(__str)}; it != std::cend(__str); ++it)
    {
        while (((it + 1) != std::cend(__str)) && (*it == *(it + 1) && (*it == ' ')))
            __str.erase(it);
    }
}

int lvt::string::lengthOfLongestSubstring(std::string_view s)
{
    /* Checking boundary conditions */
    if (s.empty())
        return 0;
    if (s.length() == 1ul)
        return 1;

    size_t posOfUniqSubstr{}; // Position of the initial character in the window
    int maxLen{};             // Length of the max unique substring
    std::string uniqSubstr;

    for (size_t i{}; i < s.length();)
    {
        // If there is no such a character in the substring - add it
        if (uniqSubstr.find(s[i]) == std::string::npos)
        {
            uniqSubstr += s[i++];

            // If position of the character is equals to the length of the initial string
            // we need to check its length with current max length and assign if it necessary
            if (i == s.length())
                maxLen = std::max(maxLen, static_cast<int>(uniqSubstr.length()));
        }
        // Otherwise:
        // 1. Compare current max length with the substring length.
        // 2. Update substring.
        // 3. Change window size.
        else
        {
            maxLen = std::max(maxLen, static_cast<int>(uniqSubstr.length()));
            uniqSubstr.clear();
            i = ++posOfUniqSubstr;
        }
    }
    return maxLen;
}

double lvt::random::create_random_double(const double &__lower, const double &__upper)
{
    return __lower + (static_cast<double>(rand()) / RAND_MAX) * (__upper - __lower);
}

std::string lvt::random::generateRandomString(size_t __lenght)
{
#ifdef __GENERATE__ALL__SYMBOLS__
    static constexpr char symbols[]{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`1234567890-=~!@#$%^&*()_+[]{}\\|/\'\",.<>:; "};
#endif

#ifdef __GENERATE__ONLY__DIGITS__
    static constexpr char onlyDigits[]{"1234567890"};
#endif

    // Declaring variable for store random string inside
    std::string rndmString{};

    // Generating random string
    for (size_t iter = 0; iter < __lenght; iter++)
    {
#ifdef __GENERATE__ALL__SYMBOLS__
        rndmString += symbols[rand() % (sizeof(symbols) - 1)];
#endif

#ifdef __GENERATE__ONLY__DIGITS__
        rndmString += onlyDigits[rand() % (sizeof(onlyDigits) - 1)];

        // To avoid numbers like 03, 045 etc.
        if (rndmString[iter] == '0')
            rndmString.erase(iter);
#endif
    }

    return rndmString;
}

std::vector<int> lvt::random::generateRandomIntVector(size_t vecSize, int from, int to)
{
    // Initializing vector with size 'vecSize'
    std::vector<int> vec(vecSize);

    // Create an instance of an engine
    std::random_device rdm_device;

    // Specify engine and distribution
    std::mt19937 engine{rdm_device()};

    // Generating random integer numbers
    std::uniform_int_distribution<int> dist{from, to};
    std::generate(std::begin(vec), std::end(vec), [&dist, &engine]()
                  { return dist(engine); });

    return vec;
}

std::vector<std::vector<int>> lvt::random::generateRandomIntMatrix(size_t rows, size_t cols,
                                                                   int offset, int range)
{
    srand(std::time(nullptr));

    // Allocating necessary memory for matrix
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
    for (size_t row{}; row < rows; row++)
        for (size_t col{}; col < cols; col++)
            matrix.at(row).at(col) = offset + (rand() % range);
    return matrix;
}

void lvt::random::fillVector(std::vector<int> &v, int from, int to)
{
    std::random_device seeder;

    // If "std::random_device" doesn't have an entropy -> using old C-style seed
    // represented as a current time in "unsigned long" representation
    // Otherwise call the ctor of the "std::random_device" instance
    const auto seed{seeder.entropy() ? seeder() : std::time(nullptr)};

    // Using Mersene twister engine as generator of integer numbers
    std::mt19937 engine{static_cast<std::mt19937::result_type>(seed)};
    std::uniform_int_distribution<int> uid{from, to};
    auto generator{std::bind(uid, engine)};
    std::generate(std::begin(v), std::end(v), generator);
}

std::vector<std::string> algorithm::split_str(const std::string &__str, const std::string &__delimiter)
{
    std::vector<std::string> splitted_str;
    std::string str(__str);

    // Splitting string on words
    size_t pos{str.find(__delimiter)}, initial_pos{0UL};
    while (pos != std::string::npos)
    {
        splitted_str.push_back(str.substr(initial_pos, pos - initial_pos));
        initial_pos = pos + 1UL;
        pos = str.find(__delimiter, initial_pos);
    }

    // Adding last word
    splitted_str.push_back(str.substr(initial_pos, std::min(pos, str.size()) - initial_pos + 1));

    return splitted_str;
}

std::string algorithm::vec_to_str(const std::vector<std::string> &__vec)
{
    std::string single_str("");
    for (const auto &word : __vec)
    {
        single_str += word + " ";
    }
    return single_str;
}

std::string algorithm::vec_to_str(std::span<const std::string> __vec)
{
    std::string single_str("");
    for (const auto &word : __vec)
    {
        single_str += word + " ";
    }
    return single_str;
}

std::vector<std::string> algorithm::splitVecStringBy(std::string &str, char delim) noexcept
{
    std::vector<std::string> vec;
    std::stringstream ss(str);
    while (std::getline(ss, str, delim))
    {
        vec.push_back(str);
    }
    return vec;
}

int algorithm::countOfUniqueSymbols(const std::string &str)
{
    std::map<char, int> m;
    size_t i{0UL};

    while (i < str.length())
    {
        m[str[i]]++;
        i++;
    }

    return m.size();
}

int algorithm::sumOfOnlyDigits(std::string str)
{
    return std::accumulate(std::begin(str), std::end(str), 0, [](unsigned i, char &ch)
                           { return std::isdigit(ch) ? i + (ch - '0') : i; });
}

constexpr int algorithm::firstCountOfConsecutiveOccurrences(const std::string &s)
{
    // Keep the end of the string, and point i to the first run's beginning
    auto endIter{std::cend(s)}, nextConsecPairIter{std::adjacent_find(std::cbegin(s), endIter)};
    if (nextConsecPairIter == endIter)
        return 0;
    else
    {
        auto next{std::find_if(nextConsecPairIter, endIter, [&nextConsecPairIter](char c)
                               { return c != *nextConsecPairIter; })};
        return std::distance(nextConsecPairIter, next);
    }
}

constexpr int algorithm::countOfConsecutiveOccurrencesAt_n(const std::string &s, size_t n)
{
    // Keep the end of the string, and point i to the first run's beginning
    auto endIter{std::cend(s)}, nextConsecPairIter{std::adjacent_find(std::cbegin(s), endIter)};
    // Vector that stores counters of consecutive elements
    std::vector<int> counterVec;
    if (nextConsecPairIter == endIter)
        return 0;
    else
        // Until reached the end of the string
        while (nextConsecPairIter not_eq endIter)
        {
            // Locate the end of the run (that is, the first different letter)
            auto next{std::find_if(nextConsecPairIter, endIter, [&nextConsecPairIter](char c)
                                   { return c != *nextConsecPairIter; })};

            counterVec.push_back(std::distance(nextConsecPairIter, next));

            // Skip to the next run's beginning
            nextConsecPairIter = std::adjacent_find(next, endIter);
        }

    return (n - 1UL < counterVec.size()) ? counterVec.at(n - 1UL) : 0;
}

constexpr int algorithm::maxCountOfConsecutiveOccurrences(const std::string &s)
{
    // Keep the end of the string, and point i to the first run's beginning
    auto endIter{std::cend(s)}, nextConsecPairIter{std::adjacent_find(std::cbegin(s), endIter)};

    // Vector that stores counters of consecutive elements
    std::vector<int> counterVec;

    if (nextConsecPairIter == endIter)
        return 0;
    else
        // Until reached the end of the string
        while (nextConsecPairIter not_eq endIter)
        {
            // Locate the end of the run (that is, the first different letter)
            auto next{std::find_if(nextConsecPairIter, endIter, [&nextConsecPairIter](char c)
                                   { return c != *nextConsecPairIter; })};

            counterVec.push_back(std::distance(nextConsecPairIter, next));

            // Skip to the next run's beginning
            nextConsecPairIter = std::adjacent_find(next, endIter);
        }

    return *std::max_element(std::cbegin(counterVec), std::cend(counterVec));
}

std::vector<std::pair<char, int>> algorithm::compressTheVectorOfPairs(std::vector<std::string> const &lstOfArt)
{
    // Getting vector of all categories of books and it's count
    std::vector<std::pair<char, int>> vec{{'A', 0}, {'B', 0}, {'C', 0}, {'D', 0}, {'E', 0}, {'F', 0}, {'G', 0}, {'H', 0}, {'I', 0}, {'J', 0}, {'K', 0}, {'L', 0}, {'M', 0}, {'N', 0}, {'O', 0}, {'P', 0}, {'Q', 0}, {'R', 0}, {'S', 0}, {'T', 0}, {'U', 0}, {'V', 0}, {'W', 0}, {'X', 0}, {'Y', 0}, {'Z', 0}};
    for (auto const &art : lstOfArt)
        vec.push_back(std::make_pair(*std::cbegin(art), std::stoi(art.substr(art.find(' ')))));

    // Sorting this vector in ascending order
    std::sort(std::begin(vec), std::end(vec));

    // Creating map, that's counts the repeats of categories in 'vec' vector
    std::map<char, int> m;
    for (auto const &el : vec)
    {
        m[el.first]++;
    }

    // Creating new vector to return it as a result
    // This vector wouldn't store the repeats, only unique keys (pair.first = key)
    std::vector<std::pair<char, int>> newVec;

    // Iterating over the map
    for (auto const &el : m)
    {
        int sum{};
        // Iterating over the vector 'vec'
        for (size_t i{}; i < vec.size(); i++)
        {
            // If first letter of category of map is the same with
            // first letter of category of vector -> get previous and next indeces
            if (el.first == vec.at(i).first)
            {
                size_t prevIdx{i}, nextIdx{prevIdx + static_cast<size_t>(m.at(vec.at(i).first))};
                // Iterating in vector where keys are non-unique and sum their values
                for (size_t j{prevIdx}; j < nextIdx; j++)
                    sum += vec.at(j).second;
                // Then break the loop to avoid repeating
                break;
            }
        }
        // Filling up the new vector 'newVec' with the only unique keys and sum
        // of their values
        newVec.push_back(std::make_pair<char, int>(std::forward<char>(const_cast<char &>(el.first)),
                                                   std::forward<int>(sum)));
    }
    return newVec;
}

std::vector<std::string> lvt::algorithm::regexFindAll(std::string const &strToSearch, std::string const &pattern, int isMatch)
{
    // Initializing "std::regex" object (converting string with pattern to a regex)
    const std::regex re_pattern(pattern);
    std::smatch sm;
    std::vector<std::string> vec;
    // Copying all matched or not matched (in relation to 'isMatch' flag) elements to the vector
    std::copy(std::sregex_token_iterator(std::cbegin(strToSearch), std::cend(strToSearch), re_pattern, isMatch),
              std::sregex_token_iterator(), std::back_inserter(vec));
    return vec;
}

void lvt::algorithm::removePunct(std::string &str)
{
    auto it{str.cbegin()};
    while (it != str.cend())
    {
        if (ispunct(*it))
            str.erase(it);
        ++it;
    }

    // Erasing last symbol if it is a endline symbol
    if (*(str.cend() - 1) == '\n')
        str.erase(str.cend() - 1);
}

bool lvt::algorithm::isContains(const std::vector<std::string> &v, const std::string &s)
{
    for (const auto &word : v)
        if (s == word)
            return true;
    return false;
}

std::vector<std::string> lvt::algorithm::getWordsInSameContexts(const std::string &text)
{
    // Making a copy of text
    std::string textCopy(text);

    // At first removing all punctuation and last endline symbol ('\n')
    removePunct(textCopy);

    // Splitting text by words and creating result vector of words in same contexts
    std::vector<std::string> vec(split_str(textCopy)), wordsInSameContexts;

    /* --- Comparing pairs of words in the text --- */
    // Getting words with even indeces (i, i + 2, i + 4, ..., where i = 0)
    for (auto fst{vec.cbegin()}, snd{std::next(std::next(fst))};
         fst != vec.cend() && snd != vec.cend(); ++fst, ++snd)
    {
        // Getting words with odd indeces (i + 1, i + 3, i + 5, ..., where i = 0)
        for (auto anotherFst{fst + 1}, anotherSnd{std::next(std::next(anotherFst))};
             anotherFst != vec.cend() && anotherSnd != vec.cend(); ++anotherFst, ++anotherSnd)
        {
            // Comparing them and if they are equal -> adding them to the vector
            if (*fst == *anotherFst && *snd == *anotherSnd)
            {
                if (!isContains(wordsInSameContexts, *std::next(fst)))
                    wordsInSameContexts.emplace_back(*std::next(fst));
                if (!isContains(wordsInSameContexts, *std::prev(anotherSnd)))
                    wordsInSameContexts.emplace_back(*std::prev(anotherSnd));
            }
        }
    }
    return wordsInSameContexts;
}

int lvt::algorithm::calculateIntervalsLength(std::vector<std::pair<int, int>> intervals)
{
    // Sorting intervals in ascending order
    std::sort(std::begin(intervals), std::end(intervals));

    // Calculating total length while maintaining a boundary variable to keep track
    // of the last processed final value
    // Desc of a lambda: Handles overlapping intervals
    return std::accumulate(intervals.begin(), intervals.end(), 0,
                           [bound = intervals[0].first](int sum, const auto &p) mutable
                           { 
                                if (bound < p.second) 
                                { 
                                    sum += (p.second - std::max(bound, p.first));
                                    bound = p.second; 
                                } 
                            return sum; });
}

std::vector<std::string> lvt::algorithm::stringPermutations(std::string s)
{
    // Checking of string
    if (s.empty())
        return {""};

    std::vector<std::string> perms;

    // Sorting copy of the string to create permutations
    std::sort(std::begin(s), std::end(s));

    do
    {
        // Adding next permutation
        perms.push_back(s);

        // Checking condition after inserting
    } while (std::next_permutation(std::begin(s), std::end(s)));

    // Returning result as a vector from unordered set
    return perms;
}

std::vector<int> lvt::algorithm::tribonacci(std::vector<int> signature, int n)
{
    // Checking bounds
    if (signature.empty() || signature.size() < 3ul)
        return {};

    // Checking if 'n' is less ore equals than size of the passed sequence
    if (static_cast<size_t>(n) <= signature.size())
        signature.resize(n);

    // Getting new values from Tribonacci sequence
    for (int i{3ul}; i < n; i++)
        signature.emplace_back(signature.at(i - 1) + signature.at(i - 2) + signature.at(i - 3));

    return signature;
}

std::string lvt::algorithm::commonLetters(std::vector<std::string> const &words)
{
    if (words.empty())
        return "";

    std::map<char, size_t> m;
    for (std::string_view word : words)
    {
        std::set<char> letters(word.begin(), word.end());
        for (char letter : letters)
            m[letter]++;
    }

    std::string str;
    for (auto const &[key, value] : m)
        if (value == words.size())
            str += key;

    return str;
}

std::string lvt::algorithm::join(std::span<std::string_view> tokens, std::string_view delim)
{
    std::string result;

    // Joining each string into result variavle
    for (std::string_view token : tokens)
    {
        result += token;
        result += delim;
    }

    // Do not need to include last added delimiter into result string
    return result.substr(0, result.length() - 1);
}

std::vector<std::string> lvt::algorithm::extractNonEmptyDirs(std::vector<std::string> dirs)
{
    if (dirs.empty())
        return {};

    std::set<std::string> s;
    for (std::string_view path : dirs)
        for (size_t i{}; i < path.length(); i++)
            if (path[i] == '/')
                s.insert(std::string(path.substr(0, i + 1)));

    return std::vector<std::string>(std::cbegin(s), std::cend(s));
}

std::vector<std::pair<std::string, int>> lvt::algorithm::calculateNGramFrequencies(std::vector<std::string> const &words,
                                                                                   size_t lengthOfNGramm)
{
    // Check boundary conditons
    if (words.empty())
        return {};

    std::map<std::string, int> m;
    for (auto const &word : words)
        // Adding specified by condition length of the word ('n') to the map
        for (size_t j{lengthOfNGramm}; j <= word.length(); ++j)
            ++m[word.substr(j - lengthOfNGramm, lengthOfNGramm)];

    // Initializing vector of pairs with values from the map
    std::vector<std::pair<std::string, int>> v(std::cbegin(m), std::cend(m));

    // Sorting by frequency of the keys
    std::sort(std::begin(v), std::end(v), [](auto const &pair1, auto const &pair2)
              { return std::tie(pair2.second, pair1.first) <
                       std::tie(pair1.second, pair2.first); });
    return v;
}

// Calculates sum of 2 big numbers represented as array of integer
void big_numbers::sum(const std::vector<int> &num1, const std::vector<int> &num2, std::vector<int> &res)
{
    size_t pos{num1.size() - 1UL};
    int carry{0};
    while (pos not_eq 0)
    {
        int total{num1.at(pos) + num2.at(pos) + carry};
        res[pos + 1UL] = total % 10;

        if (total > 9)
            carry = 1;
        else
            carry = 0;

        pos--;
    }
    res[0UL] = carry;
}

// Calculates product of 2 big numbers represented as array of integer
void big_numbers::product(const std::vector<int> &num1, const std::vector<int> &num2, std::vector<int> &res)
{
    size_t pos{res.size() - 1UL};

    // Zeroing out all values in the 'res' array
    for (size_t i{0UL}; i < res.size(); i++)
    {
        res.at(i) = 0;
    }

    for (size_t i{num1.size() - 1UL}; i not_eq 0; i--)
    {
        size_t off{num1.size() - 1UL - i};

        for (size_t j{num2.size() - 1}; j not_eq 0; j--)
        {
            int prod{num1.at(i) * num2.at(j)};

            res.at(pos - off) += prod % 10;
            res.at(pos - off - 1UL) += res.at(pos - off) / 10 + prod / 10;
            res.at(pos - off) %= 10;
        }
    }
}

// Returns factorial of number
std::string big_numbers::factorial(const int num)
{
    std::vector vec{1};
    int c{0};
    for (int i{1}; i <= num; i++)
    {
        for (auto &d : vec)
        {
            int v{d * i + c};
            d = v % 10;
            c = v / 10;
        }
        for (; c > 0; c /= 10)
            vec.push_back(c % 10);
    }

    std::stringstream ss;
    std::copy(std::rbegin(vec), std::rend(vec), std::ostream_iterator<int>(ss));
    return ss.str();
}

// Printing current time to terminal at specified format
void lvt::time::printCurTime(const StringConvertible auto str = "%H:%M:%S")
{
    std::chrono::system_clock::time_point tp{std::chrono::system_clock::now()};
    time_t tt{std::chrono::system_clock::to_time_t(tp)};
    tm *t{localtime(&tt)};
    std::stringstream ss;
    ss << std::put_time(t, str);
    std::cout << ss.str() << std::endl;
}

// Printing duration of executing some code snippet
// At first, where do you want to start the timer, you need to write following line:
// auto start{std::chrono::high_resolution_clock::now()};
// and then execute this func
void lvt::time::printExecutionTime(const auto &start)
{
    auto end{std::chrono::high_resolution_clock::now()};
    auto diff{end - start};
    std::cout << std::chrono::duration<double, std::milli>{diff}.count() << "ms" << std::endl;

    /* The line above is equals to next line: */
    // std::cout << std::chrono::duration<double, std::ratio<1, 1'000>>{diff}.count() << "ms" << std::endl;

    /* If you want to print result in seconds, use this: */
    // std::cout << std::chrono::duration<double>{diff}.count() << "s" << std::endl;
}

std::time_t lvt::time::str_to_time_t(std::string const &str, const char *format)
{
    struct std::tm tm;
    std::istringstream ss(str);
    ss >> std::get_time(&tm, format);
    return mktime(&tm);
}

std::string lvt::time::time_t_to_str(std::time_t const &time, char const *format)
{
    char buf[32];
    std::strftime(buf, 32, format, std::localtime(&time));
    return buf;
}

std::string lvt::time::generateRandomDateOfBirth(int lowestAge, int highestAge)
{
    srand(std::time(nullptr));
    std::chrono::system_clock::time_point tp(std::chrono::system_clock::now());
    std::time_t tt{std::chrono::system_clock::to_time_t(tp)};
    struct std::tm tm_;
    int currentYear{(*std::localtime(&tt)).tm_year + 1900}, randomAge{};
    tm_.tm_mday = rand() % 31 + 1;
    tm_.tm_mon = rand() % 12 + 1;
    while (randomAge < lowestAge || randomAge > highestAge)
        randomAge = rand() % highestAge + lowestAge;
    tm_.tm_year = currentYear - randomAge;
    return (std::to_string(tm_.tm_mday) + '/' + std::to_string(tm_.tm_mon) +
            '/' + std::to_string(tm_.tm_year));
}

// Returns all content from a file 'filename' as a "std::string"
std::string lvt::files::readFileToStr(std::string const &filename)
{
    std::fstream fin(filename);
    std::stringstream ss;
    ss << fin.rdbuf();
    return ss.str();
}

// Returns size of the file as a "std::size_t"
size_t lvt::files::getSizeOfTheFile(std::string const &filename)
{
    return std::filesystem::file_size(filename);
}

bool lvt::files::exists(std::string const &filename)
{
    std::ifstream ifs(filename.c_str());
    return ifs.good();
}

std::vector<std::string> lvt::files::getFilenamesByMask(std::filesystem::path const &path,
                                                        std::string const &mask)
{
    std::vector<std::string> files;
    std::regex pattern(mask);

    for (auto const &file : std::filesystem::directory_iterator(path))
        if (std::filesystem::is_regular_file(file))
        {
            std::string filename{file.path().filename().string()};

            // If 'filename' matches with the pattern - add it to vector of files
            if (std::regex_match(filename, pattern))
                files.emplace_back(filename);
        }

    return files;
}

std::vector<std::string> lvt::files::getFilenamesByMaskInDirsAndSubdirs(std::filesystem::path const &path,
                                                                        std::string const &mask)
{
    std::vector<std::string> files;
    std::regex pattern(mask);

    for (auto const &file : std::filesystem::recursive_directory_iterator(path))
        if (std::filesystem::is_regular_file(file))
        {
            std::string filename{file.path().filename().string()};

            // If 'filename' matches with the pattern - add it to vector of files
            if (std::regex_match(filename, pattern))
                files.emplace_back(filename);
        }

    return files;
}
