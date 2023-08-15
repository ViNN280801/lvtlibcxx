#ifndef LVT_IMPL_HPP
#define LVT_IMPL_HPP

#include "lvt.hpp"

// Prints array to terminal
template <typename T>
void printVec(std::vector<T> const &vec)
{
    for (const auto &el : vec)
        std::cout << el << ' ';
    endl(std::cout);
}

// Since C++20 (need std::span)
// Prints range to terminal
template <typename T>
void print_range(std::span<const T> __range)
{
    for (const auto &el : __range)
        std::cout << el << ' ';
    endl(std::cout);
}

// Prints range to terminal by iterators
template <typename Iter>
void print_range(Iter begin, Iter end)
{
    for (auto iter{begin}; iter != end; ++iter)
        std::cout << *iter << ' ';
    endl(std::cout);
}

// Prints matrix to terminal
template <typename T>
void printMatrix(std::vector<std::vector<T>> const &matrix)
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
void print_pair_vec(const std::vector<std::pair<T1, T2>> &__vec)
{
    for (size_t index{0UL}; index < __vec.size(); index++)
    {
        std::cout << "array[" << __vec.at(index).first << "] = " << __vec.at(index).second << std::endl;
    }
}

// Prints dictionary to terminal (need std::map)
template <typename T1, typename T2>
void print_dictionary(const std::map<T1, T2> &__dictionary)
{
    for (const auto &pair : __dictionary)
    {
        std::cout << pair.first << " - " << pair.second << '\n';
    }
}

// Prints tuple to terminal (need std::tuple)
template <typename TupleType, size_t TupleSize>
void printTuple(const TupleType &t)
{
    if constexpr (TupleSize > 1)
        printTuple<TupleType, TupleSize - 1>(t);

    std::cout << std::get<TupleSize - 1>(t) << std::endl;
}

// Returns true if both are equals
template <typename T>
bool is_equal(const T &__num1, const T &__num2)
{
    return (__num1 == __num2) ? true : false;
}

// Returns true if first lower than the second
template <typename T>
bool is_lower(const T &__num1, const T &__num2)
{
    return (__num1 < __num2) ? true : false;
}

// Returns true if first bigger than the second
template <typename T>
bool is_bigger(const T &__num1, const T &__num2)
{
    return (__num1 > __num2) ? true : false;
}

// Returns true if string is a unsigned integer number (unsigned short, unsigned int, size_t, etc.)
bool is_uint_number(const std::string &__str)
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
bool is_int_number(const std::string &__str)
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
bool is_floating_number(const std::string &__str)
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

// Returns "true" if type of passed arg is arythmetic type of 'char'
template <typename T>
consteval bool isArithmeticType([[maybe_unused]] const T &val) noexcept
{
    if constexpr (std::is_integral_v<T> || std::is_signed_v<T> ||
                  std::is_unsigned_v<T> || std::is_floating_point_v<T>)
        return true;
    return false;
}

// Returns string parameter as T
template <typename T>
T str_to_T(const std::string &__str)
{
    T value;
    std::istringstream iss(__str);
    iss >> value;
    return value;
}

// Returns array that formed from the 2d array
template <typename T>
std::vector<T> matrixToArr(std::vector<std::vector<T>> const &matrix)
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
std::string T_to_str(const T &__value)
{
    std::ostringstream oss;
    oss << __value;
    return oss.str();
}

// Returns 2d array that formed from the 1d array
template <typename T>
std::vector<std::vector<T>> arrToMatrix(std::vector<T> const &arr, size_t rows, size_t cols)
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

// Returns user's input as unsigned integer number
template <typename T>
T input_to_uint(const char *__msg)
{
    // User's input string
    std::string users_input{};

    // Using 'while' loop and string input to avoid errors
    while (true)
    {
        std::cout << __msg;
        std::cin >> users_input;

        // If 'input' is contains only of digits -> break infinity loop
        if (is_uint_number(users_input))
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
T input_to_int(const char *__msg)
{
    // User's input string
    std::string users_input{};

    // Using 'while' loop and string input to avoid errors
    while (true)
    {
        std::cout << __msg;
        std::cin >> users_input;

        // If 'input' is contains only of digits -> break infinity loop
        if (is_int_number(users_input))
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
T input_to_floating(const char *__msg)
{
    // User's input string
    std::string users_input{};

    // Using 'while' loop and string input to avoid errors
    while (true)
    {
        std::cout << __msg;
        std::cin >> users_input;

        // If 'input' is contains only of digits -> break infinity loop
        if (is_floating_number(users_input))
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

// Sorting 1d array by bubble sorting algorithm
template <typename T>
constexpr void bubbleSortAscending(std::vector<T> &arr)
{
    for (size_t i{}; i < arr.size(); i++)
        for (size_t j{}; j < arr.size(); j++)
            if (arr.at(i) < arr.at(j))
                std::swap(arr.at(i), arr.at(j));
}

// Sorting 2d array by bubble sorting algorithm
template <typename T>
constexpr void bubbleSort2DAscending(std::vector<std::vector<T>> &matrix)
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
constexpr void insertionSortAscending(std::vector<T> &vecToSort)
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
constexpr void insertionSort2DAscending(std::vector<std::vector<T>> &matrix)
{
    std::vector<T> arr(matrixToArr(matrix));
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
    matrix = arrToMatrix(arr, matrix.size(), matrix.at(0).size());
}

// Sorting vector by selection algorithm (the lowest perfonamce algorithm)
template <typename T>
constexpr void selectionSortAscending(std::vector<T> &vecToSort)
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
constexpr void selectionSort2DAscending(std::vector<std::vector<T>> &matrix)
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

// Sorting array by Shell sorting algorithm
template <typename T>
constexpr void ShellSortAscending(std::vector<T> &arr)
{
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
}

// Sorting 2d array by Shell sorting algorithm
template <typename T>
constexpr void ShellSort2DAscending(std::vector<std::vector<T>> &matrix)
{
    std::vector<int> arr(matrixToArr(matrix));
    ShellSortAscending(arr);
    matrix = arrToMatrix(arr, matrix.size(), matrix.at(0).size());
}

// Auxiliary method for quick sort algortihm
template <typename T>
constexpr void qSortAscending(std::vector<T> &arr, size_t low, size_t high)
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
        qSortAscending(arr, low, j);
    // Recursive call sorting to right side from pivot
    if (i < high && i < arr.size())
        qSortAscending(arr, i, high);
}

// Sorting array by quick sorting (Hoare sort) algorithm
template <typename T>
constexpr void quickSortAscending(std::vector<T> &arr)
{
    qSortAscending(arr, 0, arr.size() - 1);
}

// Sorting 2d array by quick sorting (Hoare sort) algorithm
template <typename T>
constexpr void quickSort2DAscending(std::vector<std::vector<T>> &matrix)
{
    std::vector<T> arr(matrixToArr(matrix));
    qSortAscending(arr, 0, arr.size() - 1);
    matrix = arrToMatrix(arr, matrix.size(), matrix.at(0).size());
}

// Sorting 1d array by bubble sorting algorithm
template <typename T>
constexpr void bubbleSortDescending(std::vector<T> &arr)
{
    for (size_t i{}; i < arr.size(); i++)
        for (size_t j{}; j < arr.size(); j++)
            if (arr.at(i) > arr.at(j))
                std::swap(arr.at(i), arr.at(j));
}

// Sorting 2d array by bubble sorting algorithm
template <typename T>
constexpr void bubbleSort2DDescending(std::vector<std::vector<T>> &matrix)
{
    for (size_t row_1{}; row_1 < matrix.size(); row_1++)
        for (size_t row_2{}; row_2 < matrix.size(); row_2++)
            for (size_t col_1{}; col_1 < matrix.at(row_1).size(); col_1++)
                for (size_t col_2{}; col_2 < matrix.at(row_2).size(); col_2++)
                    if (matrix.at(row_1).at(col_1) > matrix.at(row_2).at(col_2))
                        std::swap(matrix.at(row_1).at(col_1), matrix.at(row_2).at(col_2));
}

// Sorting elems in vector. Best case - O(n). Middle and worst cases - O(n^2)
template <typename T>
constexpr void insertionSortDescending(std::vector<T> &arr)
{
    // Iterating by vector from 2nd element to end: [begin + 1; end]
    for (size_t i{1}; i < arr.size(); i++)
    {
        // Initializing current value of vector
        T val{arr.at(i)};

        // Initializing position of previous element from 'i'
        size_t pos{i - 1};

        // While position of prev element is lower than size of vector
        // and element in this position is bigger than current value ->
        // assigning it to next element (j + 1) of vector
        while (pos < arr.size() && arr.at(pos) < val)
        {
            arr.at(pos + 1) = arr.at(pos);
            pos--;
        }
        // Assigning current element to next from previous
        arr.at(pos + 1) = val;
    }
}

// Sorting 2d array by insertion sorting algorithm
template <typename T>
constexpr void insertionSort2DDescending(std::vector<std::vector<T>> &matrix)
{
    std::vector<T> arr(matrixToArr(matrix));
    insertionSortDescending(arr);
    matrix = arrToMatrix(arr, matrix.size(), matrix.at(0).size());
}

// Sorting vector by selection algorithm (the lowest perfonamce algorithm)
template <typename T>
constexpr void selectionSortDescending(std::vector<T> &vecToSort)
{
    // Iterating over the range
    for (size_t i{}; i < vecToSort.size(); i++)
    {
        // For example, minimal element is begin element of the vector
        size_t maxPos{i};

        // Iterating over the unsorted range
        for (size_t j{i + 1UL}; j < vecToSort.size(); j++)
        {
            // If element from the unsorted range is lower than the current ->
            // assigning new position to 'maxPos' variable
            if (vecToSort.at(j) > vecToSort.at(maxPos))
                maxPos = j;
        }
        // Swap minimal element with current
        std::swap(vecToSort.at(i), vecToSort.at(maxPos));
    }
}

// Sorting 2d array by selection sorting algorithm
template <typename T>
constexpr void selectionSort2DDescending(std::vector<std::vector<T>> &matrix)
{
    for (size_t row{}; row < matrix.size(); row++)
    {
        for (size_t col{}; col < matrix.at(row).size(); col++)
        {
            size_t maxRow{row}, maxCol{col};
            T max{matrix.at(row).at(col)};

            for (size_t j{col + 1}; j < matrix.at(row).size(); j++)
            {
                if (matrix.at(row).at(j) > max)
                {
                    maxRow = row;
                    maxCol = j;
                    max = matrix.at(row).at(j);
                }
            }
            for (size_t i{row + 1}; i < matrix.size(); i++)
            {
                for (size_t j{}; j < matrix.at(row).size(); j++)
                {
                    if (matrix.at(i).at(j) > max)
                    {
                        maxRow = i;
                        maxCol = j;
                        max = matrix.at(i).at(j);
                    }
                }
            }
            matrix.at(maxRow).at(maxCol) = matrix.at(row).at(col);
            std::swap(matrix.at(row).at(col), max);
        }
    }
}

// Sorting array by Shell sorting algorithm
template <typename T>
constexpr void ShellSortDescending(std::vector<T> &arr)
{
    for (size_t interval{arr.size() / 2}; interval > 0; interval /= 2)
    {
        for (size_t i{}; i < arr.size(); i++)
        {
            T val{arr.at(i)};
            size_t j{};
            for (j = i; (j >= interval) && (arr.at(j - interval) < val); j -= interval)
            {
                arr.at(j) = arr.at(j - interval);
            }
            arr.at(j) = val;
        }
    }
}

// Sorting 2d array by Shell sorting algorithm
template <typename T>
constexpr void ShellSort2DDescending(std::vector<std::vector<T>> &matrix)
{
    std::vector<int> arr(matrixToArr(matrix));
    ShellSortDescending(arr);
    matrix = arrToMatrix(arr, matrix.size(), matrix.at(0).size());
}

// Auxiliary method for quick sort algortihm
template <typename T>
constexpr void qSortDescending(std::vector<T> &arr, size_t low, size_t high)
{
    size_t i{low}, j{high};
    // Select pivot value
    T pivot{arr.at((i + j) / 2)}, tmp{};

    while (i <= j && i < arr.size() && j < arr.size())
    {
        while (arr.at(i) > pivot && i < arr.size())
            i++;
        while (arr.at(j) < pivot && j < arr.size())
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
        qSortDescending(arr, low, j);
    // Recursive call sorting to right side from pivot
    if (i < high && i < arr.size())
        qSortDescending(arr, i, high);
}

// Sorting array by quick sorting (Hoare sort) algorithm
template <typename T>
constexpr void quickSortDescending(std::vector<T> &arr)
{
    qSortDescending(arr, 0, arr.size() - 1);
}

// Sorting 2d array by quick sorting (Hoare sort) algorithm
template <typename T>
constexpr void quickSort2DDescending(std::vector<std::vector<T>> &matrix)
{
    std::vector<T> arr(matrixToArr(matrix));
    qSortDescending(arr, 0, arr.size() - 1);
    matrix = arrToMatrix(arr, matrix.size(), matrix.at(0).size());
}

// Returns array of digits in descending order
// from integer and non-negative type of number
template <typename unumeric_t>
std::vector<int> split_number_on_digits(const unumeric_t &__number)
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
retType composeNumberWithDigits(const std::vector<T> &vec)
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
auto accumulateData(Iter begin, Iter end, StartValue start_value, Operation op)
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
void remove_same_elems(std::vector<T> &__range)
{
    for (auto it{std::cbegin(__range)}; it != std::cend(__range); ++it)
    {
        while (((it + 1) != std::cend(__range)) && (*it == *(it + 1)))
            __range.erase(it);
    }
}

// Returns vector of pairs from two vectors same length
template <typename T1, typename T2>
std::vector<std::pair<T1, T2>> make_vector_of_pairs_by_two_vectors(const std::vector<T1> &__vec1,
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

// Returns iterator on output sequence that is one-past-last element
// stored in the output sequence, which is contains all elements with their positions,
// matching a predicate in a given range
// 'first' - start iterator of the input sequence
// 'last' - end iterator of the input sequence
// 'dest' - start iterator of the output sequence
template <typename InputIter, typename OutputIter, typename Predicate>
OutputIter find_all(InputIter first, InputIter last,
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
std::vector<T> sliceVector(std::span<const T> vec, const std::integral auto &first, const std::integral auto &last)
{
    std::vector<T> res(std::cbegin(vec) + first, std::cbegin(vec) + last + 1);
    return res;
}

// Since C++ 20 (need <concepts>)
// Slicing vector from 'first' to 'last': [first, last]
template <typename T>
void sliceVector(std::vector<T> &vec, const std::integral auto &first, const std::integral auto &last)
{
    vec = std::vector(std::cbegin(vec) + first, std::cbegin(vec) + last + 1);
    vec.shrink_to_fit();
}

// Returns max subarray sum of contiguous elements in sequence
// Solves the "Maximum subarray problem" with the "Kadane's Algorithm"
template <typename T>
T maxSubarraySum(std::span<const T> arr)
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

template <typename T>
constexpr T mostFreqElem(std::span<T const> range)
{
    int maxcount{};
    T el_max_freq{};
    for (auto it{range.begin()}; it != range.end(); ++it)
    {
        int count{};
        for (auto jt{range.begin()}; jt != range.end(); ++jt)
            if (*it == *jt)
                count++;

        if (count > maxcount)
        {
            maxcount = count;
            el_max_freq = *it;
        }
    }
    return el_max_freq;
}

template <typename... Args>
constexpr std::string gen_str(Args &&...args)
{
    std::ostringstream oss;
    (oss << ... << args);
    return oss.str();
}

#endif // LVT_IMPL_HPP
