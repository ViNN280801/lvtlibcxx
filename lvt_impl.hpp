#ifndef LVT_IMPL_HPP
#define LVT_IMPL_HPP

template <typename T>
concept StringConvertible = std::is_convertible_v<T, std::string_view> ||
                            std::is_convertible_v<T, const char *> || std::is_convertible_v<T, char>;

template <typename T>
concept Comparable = requires(T a, T b) {
    {
        a < b
    } -> std::convertible_to<bool>;
    {
        a == b
    } -> std::convertible_to<bool>;
    {
        a != b
    } -> std::convertible_to<bool>;
    {
        a > b
    } -> std::convertible_to<bool>;
    {
        a <= b
    } -> std::convertible_to<bool>;
    {
        a >= b
    } -> std::convertible_to<bool>;
};

template <typename T>
concept Printable = requires(T a, std::ostream &os) {
    {
        os << a
    } -> std::same_as<std::ostream &>;
};

template <typename R, typename T>
concept Matrix = std::convertible_to<std::ranges::range_reference_t<std::ranges::range_reference_t<R>>, T>;

template <typename T>
void printVec(std::vector<T> const &vec)
{
    for (const auto &el : vec)
        std::cout << el << ' ';
    endl(std::cout);
}

template <typename T>
void print_range(std::span<const T> __range)
{
    for (const auto &el : __range)
        std::cout << el << ' ';
    endl(std::cout);
}

template <typename Iter>
void print_range(Iter begin, Iter end)
{
    for (auto iter{begin}; iter != end; ++iter)
        std::cout << *iter << ' ';
    endl(std::cout);
}

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

/**
 * @brief Prints matrix
 * @tparam matrix matrix to print
 */
template <Printable T>
void printMatrix(Matrix<T> auto const &matrix)
{
    for (size_t i{}; i < matrix.size(); i++)
    {
        for (size_t j{}; j < matrix[i].size(); j++)
            std::cout << matrix[i][j] << ' ';
        std::endl(std::cout);
    }
}

template <typename T1, typename T2>
void print_pair_vec(const std::vector<std::pair<T1, T2>> &__vec)
{
    for (size_t index{0UL}; index < __vec.size(); index++)
    {
        std::cout << "array[" << __vec.at(index).first << "] = " << __vec.at(index).second << std::endl;
    }
}

template <typename T1, typename T2>
void print_dictionary(const std::map<T1, T2> &__dictionary)
{
    for (const auto &pair : __dictionary)
    {
        std::cout << pair.first << " - " << pair.second << '\n';
    }
}

template <typename TupleType, size_t TupleSize>
void printTuple(const TupleType &t)
{
    if constexpr (TupleSize > 1)
        printTuple<TupleType, TupleSize - 1>(t);

    std::cout << std::get<TupleSize - 1>(t) << std::endl;
}

template <typename T>
bool is_equal(const T &__num1, const T &__num2)
{
    return (__num1 == __num2) ? true : false;
}

template <typename T>
bool is_lower(const T &__num1, const T &__num2)
{
    return (__num1 < __num2) ? true : false;
}

template <typename T>
bool is_bigger(const T &__num1, const T &__num2)
{
    return (__num1 > __num2) ? true : false;
}

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

template <typename T>
consteval bool isArithmeticType([[maybe_unused]] const T &val) noexcept
{
    if constexpr (std::is_integral_v<T> || std::is_signed_v<T> ||
                  std::is_unsigned_v<T> || std::is_floating_point_v<T>)
        return true;
    return false;
}

template <typename T>
T str_to_T(const std::string &__str)
{
    T value;
    std::istringstream iss(__str);
    iss >> value;
    return value;
}

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

template <typename T>
std::string T_to_str(const T &__value)
{
    std::ostringstream oss;
    oss << __value;
    return oss.str();
}

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

template <typename T>
constexpr void bubbleSortAscending(std::vector<T> &arr)
{
    for (size_t i{}; i < arr.size(); i++)
        for (size_t j{}; j < arr.size(); j++)
            if (arr.at(i) < arr.at(j))
                std::swap(arr.at(i), arr.at(j));
}

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

template <typename T>
constexpr void ShellSort2DAscending(std::vector<std::vector<T>> &matrix)
{
    std::vector<int> arr(matrixToArr(matrix));
    ShellSortAscending(arr);
    matrix = arrToMatrix(arr, matrix.size(), matrix.at(0).size());
}

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

template <typename T>
constexpr void quickSortAscending(std::vector<T> &arr)
{
    qSortAscending(arr, 0, arr.size() - 1);
}

template <typename T>
constexpr void quickSort2DAscending(std::vector<std::vector<T>> &matrix)
{
    std::vector<T> arr(matrixToArr(matrix));
    qSortAscending(arr, 0, arr.size() - 1);
    matrix = arrToMatrix(arr, matrix.size(), matrix.at(0).size());
}

template <typename T>
constexpr void bubbleSortDescending(std::vector<T> &arr)
{
    for (size_t i{}; i < arr.size(); i++)
        for (size_t j{}; j < arr.size(); j++)
            if (arr.at(i) > arr.at(j))
                std::swap(arr.at(i), arr.at(j));
}

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

template <typename T>
constexpr void insertionSort2DDescending(std::vector<std::vector<T>> &matrix)
{
    std::vector<T> arr(matrixToArr(matrix));
    insertionSortDescending(arr);
    matrix = arrToMatrix(arr, matrix.size(), matrix.at(0).size());
}

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

template <typename T>
constexpr void ShellSort2DDescending(std::vector<std::vector<T>> &matrix)
{
    std::vector<int> arr(matrixToArr(matrix));
    ShellSortDescending(arr);
    matrix = arrToMatrix(arr, matrix.size(), matrix.at(0).size());
}

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

template <typename T>
constexpr void quickSortDescending(std::vector<T> &arr)
{
    qSortDescending(arr, 0, arr.size() - 1);
}

template <typename T>
constexpr void quickSort2DDescending(std::vector<std::vector<T>> &matrix)
{
    std::vector<T> arr(matrixToArr(matrix));
    qSortDescending(arr, 0, arr.size() - 1);
    matrix = arrToMatrix(arr, matrix.size(), matrix.at(0).size());
}

template <Comparable T>
constexpr void mergeSortAscendingHelper(std::vector<T> &arr, std::vector<T> &result, size_t start, size_t end)
{
    // Base case: if array consist of 1 element - do nothing
    if (end - start <= 1ul)
        return;
    // If array consist of 2 elements and it's need to swap them - swap them
    if (end - start == 2ul)
    {
        if (result.at(start) > result.at(start + 1))
            std::swap(result.at(start), result.at(start + 1));
        return;
    }

    size_t middle{(start + end) / 2};

    mergeSortHelper(result, arr, start, middle);
    mergeSortHelper(result, arr, middle, end);

    // Merging left and right subarrays
    // 'k' - index for result array
    size_t i{start}, j{middle}, k{start};

    // Filling result subarray with sorted values
    while (k < end)
    {
        if (j >= end || (i < middle && arr.at(i) < arr.at(j)))
        {
            // Filling with elements of left subarray
            result.at(k) = arr.at(i);
            i++;
        }
        else
        {
            // Filling with elements with right subarray
            result.at(k) = arr.at(j);
            j++;
        }
        k++;
    }
}

template <Comparable T>
constexpr void mergeSortAscending(std::vector<T> &vec)
{
    std::vector<T> copy(vec);
    mergeSortAscendingHelper(copy, vec, 0, vec.size());
}

template <Comparable T>
constexpr void mergeSortDescendingHelper(std::vector<T> &arr, std::vector<T> &result, size_t start, size_t end)
{
    // Base case: if array consist of 1 element - do nothing
    if (end - start <= 1ul)
        return;
    // If array consist of 2 elements and it's need to swap them - swap them
    if (end - start == 2ul)
    {
        if (result.at(start) < result.at(start + 1))
            std::swap(result.at(start), result.at(start + 1));
        return;
    }

    size_t middle{(start + end) / 2};

    mergeSortHelper(result, arr, start, middle);
    mergeSortHelper(result, arr, middle, end);

    // Merging left and right subarrays
    // 'k' - index for result array
    size_t i{start}, j{middle}, k{start};

    // Filling result subarray with sorted values
    while (k < end)
    {
        if (j >= end || (i < middle && arr.at(i) > arr.at(j)))
        {
            // Filling with elements of left subarray
            result.at(k) = arr.at(i);
            i++;
        }
        else
        {
            // Filling with elements with right subarray
            result.at(k) = arr.at(j);
            j++;
        }
        k++;
    }
}

template <Comparable T>
constexpr void mergeSortDescending(std::vector<T> &vec)
{
    std::vector<T> copy(vec);
    mergeSortDescendingHelper(copy, vec, 0, vec.size());
}

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

template <typename T>
void remove_same_elems(std::vector<T> &__range)
{
    for (auto it{std::cbegin(__range)}; it != std::cend(__range); ++it)
    {
        while (((it + 1) != std::cend(__range)) && (*it == *(it + 1)))
            __range.erase(it);
    }
}

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

template <typename T>
std::vector<T> sliceVector(std::span<const T> vec, const std::integral auto &first, const std::integral auto &last)
{
    std::vector<T> res(std::cbegin(vec) + first, std::cbegin(vec) + last + 1);
    return res;
}

template <typename T>
void sliceVector(std::vector<T> &vec, const std::integral auto &first, const std::integral auto &last)
{
    vec = std::vector(std::cbegin(vec) + first, std::cbegin(vec) + last + 1);
    vec.shrink_to_fit();
}

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

template <typename T, std::integral U>
constexpr std::vector<T> kMostFreqElem(std::span<T const> range, U k)
{
    // Dictionary to count the occurrences of each element
    std::map<T, int> counts;

    // Count the occurrences of each element
    for (T const &el : range)
        counts[el]++;

    // Create a vector of pairs where each pair contains the element and its count
    std::vector<std::pair<T, int>> countPairs;
    for (auto const &el_and_count : counts)
        countPairs.push_back({el_and_count.first, el_and_count.second});

    // Sort the vector of pairs by count in descending order
    std::ranges::sort(countPairs, [](auto const &a, auto const &b)
                      { return a.second > b.second; });

    // Extract the first 'k' elements from the sorted vector
    std::vector<T> result;
    for (size_t i{}; i < static_cast<size_t>(k) && i < countPairs.size(); i++)
        result.emplace_back(countPairs[i].first);

    return result;
}

template <std::integral T>
constexpr T findClosest(std::span<T const> range, T value)
{
    // Make a copy of elements
    std::vector<T> sorted;
    std::ranges::copy(range, std::back_inserter(sorted));

    // Sorting elements in ascending order
    std::ranges::sort(sorted);

    // Finds the iterator pointing to the first element in the 'range'
    // that is greater than or equal to 'value'
    auto const it{std::lower_bound(std::cbegin(sorted), std::cend(sorted), value)};

    // If iterator points to the beginning of the range - return first element
    if (it == std::cbegin(sorted))
        return sorted.front();

    // If iterator points beyond the end of the range - return last element
    if (it == std::cend(sorted))
        return sorted.back();

    // Otherwise return the closest element
    return (*it - value < value - *(std::prev(it))) ? *it : *(std::prev(it));
}

template <std::integral T>
constexpr std::vector<T> getUniqueElementsFromTwoSequences(std::span<T const> rangeA, std::span<T const> rangeB)
{
    // Copying all elements from the both of ranges to one vector
    std::vector<T> uniqVec(rangeA.begin(), rangeA.end());
    std::ranges::copy(rangeB, std::back_inserter(uniqVec));

    // Sorting vector
    std::ranges::sort(uniqVec);

    // Removing all non-unique elems
    auto it{std::remove_if(uniqVec.begin(), uniqVec.end(), [&uniqVec](T const &val)
                           { return std::ranges::count(uniqVec, val) > 1; })};

    // Erase the removed elements
    uniqVec.erase(it, uniqVec.end());

    return uniqVec;
}

template <std::integral T>
constexpr std::vector<T> sumOfPolynomials(std::span<T const> a, std::span<T const> b)
{
    std::vector<T> minSizeArr, maxSizeArr, result;

    // Determining arrays with the minimal and maximal sizes
    if (a.size() > b.size())
    {
        minSizeArr.assign(b.begin(), b.end());
        maxSizeArr.assign(a.begin(), a.end());
    }
    else
    {
        minSizeArr.assign(a.begin(), a.end());
        maxSizeArr.assign(b.begin(), b.end());
    }

    // Reversing order of the coefs
    std::ranges::reverse(minSizeArr);
    std::ranges::reverse(maxSizeArr);

    // Add space to the result array
    result.resize(maxSizeArr.size());

    // Summation of the coefs
    for (size_t i{}; i < maxSizeArr.size(); i++)
        (i < minSizeArr.size()) ? result.at(i) = minSizeArr.at(i) + maxSizeArr.at(i) : result.at(i) = maxSizeArr.at(i);

    // Bringing result polynomial to the correct order
    std::ranges::reverse(result);
    return result;
}

template <std::integral T>
std::vector<std::vector<T>> sumOfTheMatrices(Matrix<T> auto const &a, Matrix<T> auto const &b)
{
    if (a.size() != b.size() && a.at(0ul).size() != b.at(0ul).size())
        return {{}};

    std::vector<std::vector<T>> result(a.size(), std::vector<T>(a.at(0ul).size()));

    for (size_t i{}; i < a.size(); i++)
        for (size_t j{}; j < a.at(i).size(); j++)
            result.at(i).at(j) = a.at(i).at(j) + b.at(i).at(j);

    return result;
}

template <typename... Args>
constexpr std::string gen_str(Args &&...args)
{
    std::ostringstream oss;
    (oss << ... << args);
    return oss.str();
}

#endif // LVT_IMPL_HPP
