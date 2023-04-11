#include "lvt.hpp"

using namespace lvt;

// Prints array to terminal
template <typename T>
void lvt::print::printVec(std::vector<T> const &vec)
{
    for (const auto &el : vec)
        std::cout << el << ' ';
    endl(std::cout);
}

// Since C++20 (need std::span)
// Prints range to terminal
template <typename T>
void lvt::print::print_range(std::span<const T> __range)
{
    for (const auto &el : __range)
        std::cout << el << ' ';
    endl(std::cout);
}

// Prints range to terminal by iterators
template <typename Iter>
void lvt::print::print_range(Iter begin, Iter end)
{
    for (auto iter{begin}; iter != end; ++iter)
        std::cout << *iter << ' ';
    endl(std::cout);
}

// Prints matrix to terminal
template <typename T>
void lvt::print::printMatrix(std::vector<std::vector<T>> const &matrix)
{
    for (size_t row{}; row < matrix.size(); row++)
    {
        for (size_t col{}; col < matrix.at(row).size(); col++)
            std::cout << matrix.at(row).at(col) << '\t';
        std::endl(std::cout);
    }
}

// Prints vector of pairs to terminal
template <typename T1, typename T2>
void lvt::print::print_pair_vec(const std::vector<std::pair<T1, T2>> &__vec)
{
    for (size_t index{0UL}; index < __vec.size(); index++)
    {
        std::cout << "array[" << __vec.at(index).first << "] = " << __vec.at(index).second << std::endl;
    }
}

// Prints dictionary to terminal (need std::map)
template <typename T1, typename T2>
void lvt::print::print_dictionary(const std::map<T1, T2> &__dictionary)
{
    for (const auto &pair : __dictionary)
    {
        std::cout << pair.first << " - " << pair.second << '\n';
    }
}

// Prints tuple to terminal (need std::tuple)
template <typename TupleType, size_t TupleSize>
void lvt::print::printTuple(const TupleType &t)
{
    if constexpr (TupleSize > 1)
        printTuple<TupleType, TupleSize - 1>(t);

    std::cout << std::get<TupleSize - 1>(t) << std::endl;
}

// Returns true if both are equals
template <typename T>
bool lvt::checkings::is_equal(const T &__num1, const T &__num2)
{
    return (__num1 == __num2) ? true : false;
}

// Returns true if first lower than the second
template <typename T>
bool lvt::checkings::is_lower(const T &__num1, const T &__num2)
{
    return (__num1 < __num2) ? true : false;
}

// Returns true if first bigger than the second
template <typename T>
bool lvt::checkings::is_bigger(const T &__num1, const T &__num2)
{
    return (__num1 > __num2) ? true : false;
}

// Returns "true" if '__ch' is vowel, otherwise - "false"
bool lvt::checkings::is_vowel(const char &__ch)
{
    return (__ch == 'a' || __ch == 'e' || __ch == 'i' || __ch == 'o' ||
            __ch == 'u' || __ch == 'A' || __ch == 'E' ||
            __ch == 'I' || __ch == 'O' || __ch == 'U')
               ? true
               : false;
}

// Returns "true" if type of passed arg is arythmetic type of 'char'
template <typename T>
consteval bool lvt::checkings::isArithmeticType([[maybe_unused]] const T &val) noexcept
{
    if constexpr (std::is_integral_v<T> || std::is_signed_v<T> ||
                  std::is_unsigned_v<T> || std::is_floating_point_v<T>)
        return true;
    return false;
}

// Returns true if string is a unsigned integer number (unsigned short, unsigned int, size_t, etc.)
bool lvt::checkings::is_uint_number(const std::string &__str)
{
    // Iterator for '__str' variable
    std::string::const_iterator it = __str.begin();

    // Using 'while' loop to check if all symbols in string are digits
    while (it != __str.end() && std::isdigit(*it))
    {
        // Incrementing iterator
        ++it;
    }

    return ((!__str.empty()) && (it == __str.end()));
}

// Returns true if string is a signed integer number (short, int, long, etc.)
bool lvt::checkings::is_int_number(const std::string &__str)
{
    // Iterator for '__str' variable
    std::string::const_iterator it = __str.begin();

    unsigned int minus_count{0U};

    // Iterating by symbols in string
    // If symbol is minus -> incrementing counter of minuses
    while (it != __str.end() && (*it == '-'))
    {
        minus_count++;

        // Moving to next symbol
        ++it;
    }

    // Move iterator in the beginning of string
    it = __str.begin();

    if (minus_count <= 1U)
    {
        // Using 'while' loop to check if all symbols in string are digits
        while (it != __str.end() && (std::isdigit(*it) || (*it == '-')))
        {
            // Incrementing iterator
            ++it;
        }
    }

    return ((!__str.empty()) && (it == __str.end()));
}

// Returns true if string is a floating number (float, double, etc.)
bool lvt::checkings::is_floating_number(const std::string &__str)
{
    // Iterator for '__str' variable
    std::string::const_iterator it = __str.begin();

    // Count of points in string (must be 1 point in number)
    // Same thing with minus sign
    unsigned int count_point{0U}, count_minus{0U};

    // Iterating by symbols in string
    while (it != __str.end())
    {
        // Counting all minuses in string
        if ((*it == '-'))
            count_minus++;

        // Counting all points in string
        if ((*it == '.'))
            count_point++;

        // Incrementing iterator
        ++it;
    }

    // Exception case when point stay in the beginning of string
    if (__str.at(0UL) == '.')
        return false;

    // Moving iterator to the begin of string
    it = __str.begin();

    // If number contains less or 1 point or minus -> continue
    if (count_point <= 1U && count_minus <= 1U)
    {
        // Using 'while' loop to check if all symbols in string are digits
        while (it != __str.end() && (std::isdigit(*it) || (*it) == '.' || (*it) == '-'))
        {
            // Incrementing iterator
            ++it;
        }
    }

    return ((!__str.empty()) && (it == __str.end()));
}

// Returns string parameter as T
template <typename T>
T convert::str_to_T(const std::string &__str)
{
    T value;
    std::istringstream iss(__str);
    iss >> value;
    return value;
}

// Returns array that formed from the 2d array
template <typename T>
std::vector<T> convert::matrixToArr(std::vector<std::vector<T>> const &matrix)
{
    std::vector<T> arr(matrix.size() * matrix.at(0).size());
    size_t idx{};
    for (size_t row{}; row < matrix.size(); row++)
    {
        for (size_t col{}; col < matrix.at(row).size(); col++)
        {
            arr.at(idx) = matrix.at(row).at(col);
            idx++;
        }
    }
    return arr;
}

// Returns 'T' as string
template <typename T>
std::string convert::T_to_str(const T &__value)
{
    std::ostringstream oss;
    oss << __value;
    return oss.str();
}

// Returns 2d array that formed from the 1d array
template <typename T>
std::vector<std::vector<T>> convert::arrToMatrix(std::vector<T> const &arr, size_t const &rows, size_t const &cols)
{
    if (arr.size() != rows * cols)
    {
        std::cout << "The size of array and matrix don't match. Returning empty matrix..." << std::endl;
        return std::vector<std::vector<T>>{{}};
    }

    std::vector<std::vector<T>> matrix(rows, std::vector<T>(cols));
    size_t idx{};
    for (size_t row{}; row < rows && (idx < arr.size()); row++)
    {
        for (size_t col{}; col < cols; col++)
        {
            matrix.at(row).at(col) = arr.at(idx);
            idx++;
        }
    }
    return matrix;
}

// Turning all characters in string to lowercase
std::string string::modifying::str_to_lower(const std::string &__str)
{
    std::string str{__str};
    std::transform(std::begin(str), std::end(str), std::begin(str), ::tolower);
    return str;
}

// Makes all characters in string to uppercase
std::string string::modifying::str_to_upper(const std::string &__str)
{
    std::string str{__str};
    std::transform(std::begin(str), std::end(str), std::begin(str), ::toupper);
    return str;
}

// Returns string '__str' without vowels
std::string string::modifying::remove_vowels(const std::string &__str)
{
    std::string str(__str);
    str.erase(std::remove_if(std::begin(str), std::end(str), [](const char &ch)
                             { return lvt::checkings::is_vowel(ch); }),
              std::cend(str));
    return str;
}

// Since C++20 (need std::erase_if())
// Returns string '__str' without vowels
std::string string::modifying::remove_vowels_cxx_20(const std::string &__str)
{
    std::string str(__str);
    std::erase_if(str, [](const char &ch)
                  { return lvt::checkings::is_vowel(ch); });
    return str;
}

// Returns string '__str' without vowels (need std::regex)
std::string string::modifying::remove_vowels_regex(const std::string &__str)
{
    std::string str(__str);
    std::regex vowels("[aeiouAEOIOU]");
    return std::regex_replace(str, vowels, "");
}

// Returns string '__str' without vowels
void string::modifying::remove_vowels(std::string &__str)
{
    __str.erase(std::remove_if(std::begin(__str), std::end(__str), [](const char &ch)
                               { return lvt::checkings::is_vowel(ch); }),
                std::cend(__str));
}

// Since C++20 (need std::erase_if())
// Returns string '__str' without vowels
void string::modifying::remove_vowels_cxx_20(std::string &__str)
{
    std::erase_if(__str, [](const char &ch)
                  { return lvt::checkings::is_vowel(ch); });
}

// Returns string '__str' without vowels (need std::regex)
void string::modifying::remove_vowels_regex(std::string &__str)
{
    std::regex vowels("[aeiouAEOIOU]");
    std::regex_replace(__str, vowels, "");
}

// Removing consecutive same characters from some range
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

// Removing consecutive same characters from some range
void string::modifying::remove_consecutive_spaces(std::string &__str)
{
    for (auto it{std::cbegin(__str)}; it != std::cend(__str); ++it)
    {
        while (((it + 1) != std::cend(__str)) && (*it == *(it + 1) && (*it == ' ')))
            __str.erase(it);
    }
}

// Returns user's input as unsigned integer number
template <typename T>
T input::input_to_uint(const char *__msg)
{
    // User's input string
    std::string users_input{};

    // Using 'while' loop and string input to avoid errors
    while (true)
    {
        std::cout << __msg;
        std::cin >> users_input;

        // If 'input' is contains only of digits -> break infinity loop
        if (lvt::checkings::is_uint_number(users_input))
            break;
        // Else: print message and back to the begininng of 'while' loop
        else
            std::cout << "You entered not an unsigned integer number. Try again.\n";
    }

    // Converting user's string to numeric type to return it as a result
    T num{str_to_T<T>(users_input)};

    // Returning converted user's inputted value to 'T' type
    return num;
}

// Returns user's input as signed integer number
template <typename T>
T input::input_to_int(const char *__msg)
{
    // User's input string
    std::string users_input{};

    // Using 'while' loop and string input to avoid errors
    while (true)
    {
        std::cout << __msg;
        std::cin >> users_input;

        // If 'input' is contains only of digits -> break infinity loop
        if (lvt::checkings::is_int_number(users_input))
            break;
        // Else: print message and back to the begininng of 'while' loop
        else
            std::cout << "You entered not an signed integer number. Try again.\n";
    }

    // Converting user's string to numeric type to return it as a result
    T num{str_to_T<T>(users_input)};

    // Returning converted user's inputted value to 'T' type
    return num;
}

// Returns user's input as floating number
template <typename T>
T input::input_to_floating(const char *__msg)
{
    // User's input string
    std::string users_input{};

    // Using 'while' loop and string input to avoid errors
    while (true)
    {
        std::cout << __msg;
        std::cin >> users_input;

        // If 'input' is contains only of digits -> break infinity loop
        if (lvt::checkings::is_floating_number(users_input))
            break;
        // Else: print message and back to the begininng of 'while' loop
        else
            std::cout << "You entered not an floating number. Try again.\n";
    }

    // Converting user's string to numeric type to return it as a result
    T num{str_to_T<T>(users_input)};

    // Returning converted user's inputted value to 'T' type
    return num;
}

// Returns one random double number
double lvt::random::create_random_double(const double &__lower, const double &__upper)
{
    return __lower + (static_cast<double>(rand()) / RAND_MAX) * (__upper - __lower);
}

// Returns random string
/* Hint: You must declare at the top following line:
    #define __GENERATE__ALL__SYMBOLS__ for generate string consisting of all symbols
    or
    #define __GENERATE__ONLY__DIGITS__ for generate string consisting of only digits */
std::string lvt::random::generateRandomString(const size_t &__lenght)
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

// Returns random vector filled with integer numbers
// 'vecSize' - size of the vector
// 'from' - lower number
// 'to' - higher number to generate
std::vector<int> lvt::random::generateRandomIntVector(size_t const &vecSize, int const &from, int const &to)
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

// Returns matrix of integers that is filled with random numbers
// Gets rows as a first parameter and columns as a second
// Third param - offset, fourth - range
std::vector<std::vector<int>> lvt::random::generateRandomIntMatrix(size_t const &rows, size_t const &cols,
                                                                   int const &offset, int const &range)
{
    srand(std::time(nullptr));

    // Allocating necessary memory for matrix
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
    for (size_t row{}; row < rows; row++)
        for (size_t col{}; col < cols; col++)
            matrix.at(row).at(col) = offset + (rand() % range);
    return matrix;
}

// Sorting 1d array by bubble sorting algorithm
template <typename T>
constexpr void lvt::algorithm::sorting::bubbleSortAscending(std::vector<T> &arr)
{
    for (size_t i{}; i < arr.size(); i++)
        for (size_t j{}; j < arr.size(); j++)
            if (arr.at(i) < arr.at(j))
                std::swap(arr.at(i), arr.at(j));
}

// Sorting 2d array by bubble sorting algorithm
template <typename T>
constexpr void lvt::algorithm::sorting::bubbleSort2DAscending(std::vector<std::vector<T>> &matrix)
{
    for (size_t row_1{}; row_1 < matrix.size(); row_1++)
        for (size_t row_2{}; row_2 < matrix.size(); row_2++)
            for (size_t col_1{}; col_1 < matrix.at(row_1).size(); col_1++)
                for (size_t col_2{}; col_2 < matrix.at(row_2).size(); col_2++)
                    if (matrix.at(row_1).at(col_1) < matrix.at(row_2).at(col_2))
                        std::swap(matrix.at(row_1).at(col_1), matrix.at(row_2).at(col_2));
}

// Sorting elems in vector. Best case - O(n). Middle and worst cases - O(n^2)
template <typename T>
constexpr void lvt::algorithm::sorting::insertionSortAscending(std::vector<T> &vecToSort)
{
    // Iterating by vector from 2nd element to end: [begin + 1; end]
    for (size_t i{1UL}; i < vecToSort.size(); i++)
    {
        // Initializing position of previous element from 'i'
        size_t j{i - 1UL};

        // Initializing current value of vector
        T value{vecToSort[i]};

        // While position of prev element is lower than size of vector
        // and element in this position is bigger than current value ->
        // assigning it to next element (j + 1) of vector
        while (j < vecToSort.size() && vecToSort[j] > value)
        {
            vecToSort[j + 1] = vecToSort[j];
            j--;
        }
        // Assigning current element to next from previous
        vecToSort[j + 1] = value;
    }
}

// Sorting 2d array by insertion sorting algorithm
template <typename T>
constexpr void lvt::algorithm::sorting::insertionSort2DAscending(std::vector<std::vector<T>> &matrix)
{
    std::vector<T> arr(lvt::convert::matrixToArr(matrix));
    for (size_t i{1}; i < arr.size(); i++)
    {
        T val{arr.at(i)};
        size_t pos{i - 1};
        while (pos < arr.size() && arr.at(pos) > val)
        {
            arr.at(pos + 1) = arr.at(pos);
            pos--;
        }
        arr.at(pos + 1) = val;
    }
    matrix = lvt::convert::arrToMatrix(arr, matrix.size(), matrix.at(0).size());
}

// Sorting vector by selection algorithm (the lowest perfonamce algorithm)
template <typename T>
constexpr void lvt::algorithm::sorting::selectionSortAscending(std::vector<T> &vecToSort)
{
    // Iterating over the range
    for (size_t i{}; i < vecToSort.size(); i++)
    {
        // For example, minimal element is begin element of the vector
        size_t minPos{i};

        // Iterating over the unsorted range
        for (size_t j{i + 1UL}; j < vecToSort.size(); j++)
        {
            // If element from the unsorted range is lower than the current ->
            // assigning new position to 'minPos' variable
            if (vecToSort.at(j) < vecToSort.at(minPos))
                minPos = j;
        }
        // Swap minimal element with current
        std::swap(vecToSort.at(i), vecToSort.at(minPos));
    }
}

// Sorting 2d array by selection sorting algorithm
template <typename T>
constexpr void lvt::algorithm::sorting::selectionSort2DAscending(std::vector<std::vector<T>> &matrix)
{
    for (size_t row{}; row < matrix.size(); row++)
    {
        for (size_t col{}; col < matrix.at(row).size(); col++)
        {
            size_t minRow{row}, minCol{col};
            T min{matrix.at(row).at(col)};

            for (size_t j{col + 1}; j < matrix.at(row).size(); j++)
            {
                if (matrix.at(row).at(j) < min)
                {
                    minRow = row;
                    minCol = j;
                    min = matrix.at(row).at(j);
                }
            }
            for (size_t i{row + 1}; i < matrix.size(); i++)
            {
                for (size_t j{}; j < matrix.at(row).size(); j++)
                {
                    if (matrix.at(i).at(j) < min)
                    {
                        minRow = i;
                        minCol = j;
                        min = matrix.at(i).at(j);
                    }
                }
            }
            matrix.at(minRow).at(minCol) = matrix.at(row).at(col);
            std::swap(matrix.at(row).at(col), min);
        }
    }
}

// Sorting 2d array by Shell sorting algorithm
template <typename T>
constexpr void lvt::algorithm::sorting::ShellSort2DAscending(std::vector<std::vector<T>> &matrix)
{
    std::vector<int> arr(lvt::convert::matrixToArr(matrix));
    for (size_t interval{arr.size() / 2}; interval > 0; interval /= 2)
    {
        for (size_t i{}; i < arr.size(); i++)
        {
            T val{arr.at(i)};
            size_t j{};
            for (j = i; (j >= interval) && (arr.at(j - interval) > val); j -= interval)
            {
                arr.at(j) = arr.at(j - interval);
            }
            arr.at(j) = val;
        }
    }
    matrix = lvt::convert::arrToMatrix(arr, matrix.size(), matrix.at(0).size());
}

// Auxiliary method for quick sort algortihm
template <typename T>
constexpr void lvt::algorithm::sorting::qSortAscending(std::vector<T> &arr, size_t low, size_t high)
{
    size_t i{low}, j{high};
    // Select pivot value
    T pivot{arr.at((i + j) / 2)}, tmp{};

    while (i <= j && i < arr.size() && j < arr.size())
    {
        while (arr.at(i) < pivot && i < arr.size())
            i++;
        while (arr.at(j) > pivot && j < arr.size())
            j--;
        if (i <= j && i < arr.size() && j < arr.size())
        {
            tmp = arr.at(i);
            arr.at(i) = arr.at(j);
            arr.at(j) = tmp;
            i++;
            j--;
        }
    }
    // Recursive call sorting to left side from pivot
    if (j > low && j < arr.size())
        lvt::algorithm::sorting::qSortAscending(arr, low, j);
    // Recursive call sorting to right side from pivot
    if (i < high && i < arr.size())
        lvt::algorithm::sorting::qSortAscending(arr, i, high);
}

// Sorting array by quick sorting (Hoare sort) algorithm
template <typename T>
constexpr void lvt::algorithm::sorting::quickSortAscending(std::vector<T> &arr)
{
    lvt::algorithm::sorting::qSortAscending(arr, 0, arr.size() - 1);
}

// Sorting 2d array by quick sorting (Hoare sort) algorithm
template <typename T>
constexpr void lvt::algorithm::sorting::quickSort2DAscending(std::vector<std::vector<T>> &matrix)
{
    std::vector<T> arr(lvt::convert::matrixToArr(matrix));
    lvt::algorithm::sorting::qSortAscending(arr, 0, arr.size() - 1);
    matrix = lvt::convert::arrToMatrix(arr, matrix.size(), matrix.at(0).size());
}

// Returns array of digits in descending order
// from integer and non-negative type of number
template <typename unumeric_t>
std::vector<int> algorithm::split_number_on_digits(const unumeric_t &__number)
{
    std::vector<int> digits;
    unumeric_t number_copy{__number};

    while (true)
    {
        digits.push_back(number_copy % 10);
        number_copy /= 10;

        if (number_copy == 0)
            return digits;
    }
}

// Returns number by vector of digits
template <typename T, typename retType>
retType algorithm::composeNumberWithDigits(const std::vector<T> &vec)
{
    std::vector<T> vecCopy{vec};
    std::reverse(std::begin(vecCopy), std::end(vecCopy));

    retType num{}, decimal{1};
    for (const auto &digit : vecCopy)
    {
        num += digit * decimal;
        decimal *= 10;
    }

    return num;
}

// Returns result of mathematical operation 'op' that applies to each element of range
template <typename Iter, typename StartValue, typename Operation>
auto algorithm::accumulateData(Iter begin, Iter end, StartValue start_value, Operation op)
{
    auto accumulated{start_value};
    for (Iter iter{begin}; iter != end; ++iter)
    {
        accumulated = op(accumulated, *iter);
    }
    return accumulated;
}

// Removing consecutive same characters from some range
template <typename T>
void algorithm::remove_same_elems(std::vector<T> &__range)
{
    for (auto it{std::cbegin(__range)}; it != std::cend(__range); ++it)
    {
        while (((it + 1) != std::cend(__range)) && (*it == *(it + 1)))
            __range.erase(it);
    }
}

// Returns vector of pairs from two vectors same length
template <typename T1, typename T2>
std::vector<std::pair<T1, T2>> algorithm::make_vector_of_pairs_by_two_vectors(const std::vector<T1> &__vec1,
                                                                              const std::vector<T2> &__vec2)
{
    std::vector<std::pair<T1, T2>> result_vec;
    std::vector<T1> vec1(__vec1);
    std::vector<T2> vec2(__vec2);

    result_vec.reserve(__vec1.size());
    std::transform(std::begin(vec1), std::end(vec1), std::begin(vec2), std::back_inserter(result_vec),
                   [](auto value1, auto value2)
                   {
                       return std::make_pair(value1, value2);
                   });

    return result_vec;
}

// Returns vector of words in a string, except any spaces
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

// Composing vector of string to a single string
std::string algorithm::vec_to_str(const std::vector<std::string> &__vec)
{
    std::string single_str("");
    for (const auto &word : __vec)
    {
        single_str += word + " ";
    }
    return single_str;
}

// Since C++20 (need std::span)
// Composing vector of string to a single string
std::string algorithm::vec_to_str(std::span<const std::string> __vec)
{
    std::string single_str("");
    for (const auto &word : __vec)
    {
        single_str += word + " ";
    }
    return single_str;
}

// Returns iterator on output sequence that is one-past-last element
// stored in the output sequence, which is contains all elements with their positions,
// matching a predicate in a given range
// 'first' - start iterator of the input sequence
// 'last' - end iterator of the input sequence
// 'dest' - start iterator of the output sequence
template <typename InputIter, typename OutputIter, typename Predicate>
OutputIter algorithm::find_all(InputIter first, InputIter last,
                               OutputIter dest, Predicate pred)
{
    while (first not_eq last)
    {
        if (pred(*first))
        {
            *dest = first;
            ++dest;
        }
        ++first;
    }
    return dest;

    // Example:
    // vector vec{3, 4, 5, 4, 5, 6, 5, 8};
    // vector<vector<int>::iterator> matches;
    // find_all(begin(vec), end(vec), back_inserter(matches),
    //          [](int i)
    //          { return i == 5; });
    // cout << format("Found {} matching elements: ", matches.size()) << endl;
    // for (const auto &it : matches)
    // {
    //     cout << *it << " at position " << distance(begin(vec), it) << endl;
    // }
}

// Since C++ 20 (need std::span and <concepts>)
// Returns sliced vector from 'first' to 'last': [first, last]
template <typename T>
std::vector<T> algorithm::sliceVector(std::span<const T> vec, const std::integral auto &first, const std::integral auto &last)
{
    std::vector<T> res(std::cbegin(vec) + first, std::cbegin(vec) + last + 1);
    return res;
}

// Since C++ 20 (need <concepts>)
// Slicing vector from 'first' to 'last': [first, last]
template <typename T>
void algorithm::sliceVector(std::vector<T> &vec, const std::integral auto &first, const std::integral auto &last)
{
    vec = std::vector(std::cbegin(vec) + first, std::cbegin(vec) + last + 1);
    vec.shrink_to_fit();
}

// Returns max subarray sum of contiguous elements in sequence
// Solves the "Maximum subarray problem" with the "Kadane's Algorithm"
template <typename T>
T algorithm::maxSubarraySum(std::span<const T> arr)
{
    T max{0}, local{0};

    if constexpr (std::is_integral_v<T> || std::is_signed_v<T> ||
                  std::is_unsigned_v<T> || std::is_floating_point_v<T>)
    {
        for (const auto &el : arr)
        {
            local += el;

            if (local > max)
                max = local;
            if (local < 0)
                local = 0;
        }
        return max;
    }
}

// Returns vector of symbols in the string 'str', except any 'delim'eters
std::vector<std::string> algorithm::splitVecStringBy(std::string &str, const char &delim) noexcept
{
    std::vector<std::string> vec;
    std::stringstream ss(str);
    while (std::getline(ss, str, delim))
    {
        vec.push_back(str);
    }
    return vec;
}

// Returns count of unique symbols in the string 'str'
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

// Returns sum of only digits in the string 'str'
int algorithm::sumOfOnlyDigits(std::string str)
{
    return std::accumulate(std::begin(str), std::end(str), 0, [](unsigned i, char &ch)
                           { return std::isdigit(ch) ? i + (ch - '0') : i; });
}

// Returns count of the first consecutive occurrences in the string 's'
constexpr int algorithm::firstCountOfConsecutiveOccurrences(const std::string &s)
{
    // Keep the end of the string, and point i to the first run's beginning
    auto endIter{std::cend(s)}, nextConsecPairIter{std::adjacent_find(std::cbegin(s), endIter)};
    if (nextConsecPairIter == endIter)
        return 0;
    else
    {
        auto next{std::find_if(nextConsecPairIter, endIter, [&nextConsecPairIter](const char &c)
                               { return c != *nextConsecPairIter; })};
        return std::distance(nextConsecPairIter, next);
    }
}

// Returns count of the first consecutive occurrences in the string 's'
// 'n' is number of occurrence
constexpr int algorithm::countOfConsecutiveOccurrencesAt_n(const std::string &s, const size_t &n)
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
            auto next{std::find_if(nextConsecPairIter, endIter, [&nextConsecPairIter](const char &c)
                                   { return c != *nextConsecPairIter; })};

            counterVec.push_back(std::distance(nextConsecPairIter, next));

            // Skip to the next run's beginning
            nextConsecPairIter = std::adjacent_find(next, endIter);
        }

    return (n - 1UL < counterVec.size()) ? counterVec.at(n - 1UL) : 0;
}

// Returns maximum count of the consecutive occurrences in the string 's'
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
            auto next{std::find_if(nextConsecPairIter, endIter, [&nextConsecPairIter](const char &c)
                                   { return c != *nextConsecPairIter; })};

            counterVec.push_back(std::distance(nextConsecPairIter, next));

            // Skip to the next run's beginning
            nextConsecPairIter = std::adjacent_find(next, endIter);
        }

    return *std::max_element(std::cbegin(counterVec), std::cend(counterVec));
}

// Return vector of pairs that will store the only unique keys as a first value of pair
// and sum of values of repeating keys as a second value of pair
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
void lvt::time::printCurTime(const String auto str = "%H:%M:%S")
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
