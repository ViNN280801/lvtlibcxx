#ifndef LVT_HPP
#define LVT_HPP

#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <regex>
#include <span>
#include <tuple>
#include <concepts>
#include <numeric>
#include <iterator>
#include <iomanip>
#include <chrono>
#include <ratio>
#include <fstream>
#include <filesystem>
#include <random>
#include <ctime>
#include <utility>
#include <functional>

#include "lvt_impl.hpp"

using namespace std::chrono_literals;

namespace lvt
{
    /**
     * @brief Concept that specifies all types that can be convert to "std::string_view" type
     * For example, "char", "const char *", "std::string", etc.
     */
    template <typename T>
    concept StringConvertible = std::is_convertible_v<T, std::string_view>;

    /**
     * @brief Concept that checks available of all comparison operators
     * @tparam a first variable
     * @tparam b second variable
     */
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

    /**
     * @brief Concept that checks if variable has output operator
     * @tparam a variable to check
     * @param os output stream
     */
    template <typename T>
    concept Printable = requires(T a, std::ostream &os) {
        {
            os << a
        } -> std::same_as<std::ostream &>;
    };

    /**
     * @brief Describes matrix. Checks type 'R' representes a 2D-array of elements with type 'T'
     * by verifying that the elements within 'R' can be convertible to 'T'
     */
    template <typename R, typename T>
    concept Matrix = std::convertible_to<std::ranges::range_reference_t<std::ranges::range_reference_t<R>>, T>;

    namespace print
    {
        // Prints array to terminal
        template <typename T>
        extern void printVec(std::vector<T> const &);

        // Since C++20 (need std::span)
        // Prints range to terminal
        template <typename T>
        void print_range(std::span<const T>);

        // Prints range to terminal by iterators
        template <typename Iter>
        void print_range(Iter, Iter);

        // Prints matrix to terminal
        template <typename T>
        void printMatrix(std::vector<std::vector<T>> const &);

        /**
         * @brief Prints matrix
         * @tparam matrix matrix to print
         */
        template <Printable T>
        void printMatrix(Matrix<T> auto const &matrix);

        // Prints vector of pairs to terminal
        template <typename T1, typename T2>
        void print_pair_vec(const std::vector<std::pair<T1, T2>> &);

        // Prints dictionary to terminal (need std::map)
        template <typename T1, typename T2>
        void print_dictionary(const std::map<T1, T2> &);

        // Prints tuple to terminal (need std::tuple)
        template <typename TupleType, size_t TupleSize = std::tuple_size<TupleType>::value>
        void printTuple(const TupleType &);
    }

    namespace checkings
    {
        // Returns true if string is a unsigned integer number (unsigned short, unsigned int, size_t, etc.)
        bool is_uint_number(const std::string &);

        // Returns true if string is a signed integer number (short, int, long, etc.)
        bool is_int_number(const std::string &);

        // Returns true if string is a floating number (float, double, etc.)
        bool is_floating_number(const std::string &);

        // Returns true if both are equals
        template <typename T>
        bool is_equal(const T &, const T &);

        // Returns true if first lower than the second
        template <typename T>
        bool is_lower(const T &, const T &);

        // Returns true if first bigger than the second
        template <typename T>
        bool is_bigger(const T &, const T &);

        // Returns "true" if '__ch' is vowel, otherwise - "false"
        bool is_vowel(char);

        // Returns "true" if type of passed arg is arythmetic type of 'char'
        template <typename T>
        consteval bool isArithmeticType([[maybe_unused]] const T &) noexcept;
    }

    namespace convert
    {
        // Returns string parameter as T
        template <typename T>
        T str_to_T(const std::string &);

        // Returns 'T' as string
        template <typename T>
        std::string T_to_str(const T &);

        // Returns array that formed from the 2d array
        template <typename T>
        std::vector<T> matrixToArr(std::vector<std::vector<T>> const &);

        // Returns 2d array that formed from the 1d array
        template <typename T>
        std::vector<std::vector<T>> arrToMatrix(std::vector<T> const &, size_t, size_t);
    }

    namespace string
    {
        namespace modifying
        {
            // Turning all characters in string to lowercase
            std::string str_to_lower(const std::string &);

            // Makes all characters in string to uppercase
            std::string str_to_upper(const std::string &);

            // Returns string '__str' without vowels
            std::string remove_vowels(const std::string &);

            // Since C++20 (need std::erase_if())
            // Returns string '__str' without vowels
            std::string remove_vowels_cxx_20(const std::string &);

            // Returns string '__str' without vowels (need std::regex)
            std::string remove_vowels_regex(const std::string &);

            // Returns string '__str' without vowels
            void remove_vowels(std::string &__str);

            // Since C++20 (need std::erase_if())
            // Returns string '__str' without vowels
            void remove_vowels_cxx_20(std::string &);

            // Returns string '__str' without vowels (need std::regex)
            void remove_vowels_regex(std::string &);

            // Removing consecutive same characters from some range
            std::string remove_consecutive_spaces(const std::string &);

            // Removing consecutive same characters from some range
            void remove_consecutive_spaces(std::string &);
        }

        /**
         * @brief Generates string with specified multiple args
         * @tparam args arguments of type that can be convert to string
         * @return String composed from all arguments
         */
        template <typename... Args>
        constexpr std::string gen_str(Args &&...args);
    }

    namespace input
    {
        // Returns user's input as unsigned integer number
        template <typename T>
        T input_to_uint(const char *msg = "");

        // Returns user's input as signed integer number
        template <typename T>
        T input_to_int(const char *msg = "");

        // Returns user's input as floating number
        template <typename T>
        T input_to_floating(const char *msg = "");
    }

    namespace random
    {
        // Returns one random double number
        double create_random_double(const double &__lower = 0.0, const double &__upper = 10.0);

        // Returns random string
        /* Hint: You must declare at the top following line:
            #define __GENERATE__ALL__SYMBOLS__ for generate string consisting of all symbols
            or
            #define __GENERATE__ONLY__DIGITS__ for generate string consisting of only digits */
        std::string generateRandomString(size_t);

        // Returns random vector filled with integer numbers
        // 'vecSize' - size of the vector
        // 'from' - lower number
        // 'to' - higher number to generate
        std::vector<int> generateRandomIntVector(size_t vecSize = 10UL, int from = -50, int to = 50);

        // Returns matrix of integers that is filled with random numbers
        // Gets rows as a first parameter and columns as a second
        // Third param - offset, fourth - range
        std::vector<std::vector<int>> generateRandomIntMatrix(size_t rows, size_t cols,
                                                              int offset = 1, int range = 100);

        /**
         * @brief Fills vector with integer values
         * @param v vector
         * @param from min value to generate
         * @param to max value to generate
         */
        void fillVector(std::vector<int> &v, int from = 0, int to = 100);
    }

    namespace algorithm
    {
        namespace sorting
        {
            // Sorting 1d array by bubble sorting algorithm
            template <typename T>
            constexpr void bubbleSortAscending(std::vector<T> &);

            // Sorting 2d array by bubble sorting algorithm
            template <typename T>
            constexpr void bubbleSort2DAscending(std::vector<std::vector<T>> &);

            // Sorting elems in vector. Best case - O(n). Middle and worst cases - O(n^2)
            template <typename T>
            constexpr void insertionSortAscending(std::vector<T> &);

            // Sorting 2d array by insertion sorting algorithm
            template <typename T>
            constexpr void insertionSort2DAscending(std::vector<std::vector<T>> &);

            // Sorting vector by selection algorithm
            template <typename T>
            constexpr void selectionSortAscending(std::vector<T> &);

            // Sorting 2d array by selection sorting algorithm
            template <typename T>
            constexpr void selectionSort2DAscending(std::vector<std::vector<T>> &);

            // Sorting array by Shell sorting algorithm
            template <typename T>
            constexpr void ShellSortAscending(std::vector<T> &);

            // Sorting 2d array by Shell sorting algorithm
            template <typename T>
            constexpr void ShellSort2DAscending(std::vector<std::vector<T>> &);

            // Auxiliary method for quick sort algortihm
            template <typename T>
            constexpr void qSortAscending(std::vector<T> &arr, size_t, size_t);

            // Sorting array by quick sorting (Hoare sort) algorithm
            template <typename T>
            constexpr void quickSortAscending(std::vector<T> &);

            // Sorting 2d array by quick sorting (Hoare sort) algorithm
            template <typename T>
            constexpr void quickSort2DAscending(std::vector<std::vector<T>> &);

            // Sorting 1d array by bubble sorting algorithm
            template <typename T>
            constexpr void bubbleSortDescending(std::vector<T> &);

            // Sorting 2d array by bubble sorting algorithm
            template <typename T>
            constexpr void bubbleSort2DDescending(std::vector<std::vector<T>> &);

            // Sorting elems in vector. Best case - O(n). Middle and worst cases - O(n^2)
            template <typename T>
            constexpr void insertionSortDescending(std::vector<T> &);

            // Sorting 2d array by insertion sorting algorithm
            template <typename T>
            constexpr void insertionSort2DDescending(std::vector<std::vector<T>> &);

            // Sorting vector by selection algorithm
            template <typename T>
            constexpr void selectionSortDescending(std::vector<T> &);

            // Sorting 2d array by selection sorting algorithm
            template <typename T>
            constexpr void selectionSort2DDescending(std::vector<std::vector<T>> &);

            // Sorting array by Shell sorting algorithm
            template <typename T>
            constexpr void ShellSortDescending(std::vector<T> &);

            // Sorting 2d array by Shell sorting algorithm
            template <typename T>
            constexpr void ShellSort2DDescending(std::vector<std::vector<T>> &);

            // Auxiliary method for quick sort algortihm
            template <typename T>
            constexpr void qSortDescending(std::vector<T> &arr, size_t, size_t);

            // Sorting array by quick sorting (Hoare sort) algorithm
            template <typename T>
            constexpr void quickSortDescending(std::vector<T> &);

            // Sorting 2d array by quick sorting (Hoare sort) algorithm
            template <typename T>
            constexpr void quickSort2DDescending(std::vector<std::vector<T>> &);

            /**
             * @brief Recursive func helper for merge sort
             * @tparam arr array of elements -> arr[start;end)
             * @tparam result result vector
             * @param start left index
             * @param end right index
             */
            template <Comparable T>
            constexpr void mergeSortAscendingHelper(std::vector<T> &arr, std::vector<T> &result, size_t start, size_t end);

            /**
             * @brief Merge sort function. Best, middle and worth cases: 0(n*log(n))
             * @tparam vec array of elements
             */
            template <Comparable T>
            constexpr void mergeSortAscending(std::vector<T> &vec);

            /**
             * @brief Recursive func helper for merge sort
             * @tparam arr array of elements -> arr[start;end)
             * @tparam result result vector
             * @param start left index
             * @param end right index
             */
            template <Comparable T>
            constexpr void mergeSortHelper(std::vector<T> &arr, std::vector<T> &result, size_t start, size_t end);

            /**
             * @brief Merge sort function. Best, middle and worth cases: 0(n*log(n))
             * @tparam vec array of elements
             */
            template <Comparable T>
            constexpr void mergeSortDescending(std::vector<T> &vec);
        }

        // Returns array of digits in descending order
        // from integer and non-negative type of number
        template <typename unumeric_t>
        std::vector<int> split_number_on_digits(const unumeric_t &);

        // Returns number by vector of digits
        template <typename T = int, typename retType = T>
        retType composeNumberWithDigits(const std::vector<T> &vec);

        // Returns result of mathematical operation 'op' that applies to each element of range
        template <typename Iter, typename StartValue, typename Operation>
        auto accumulateData(Iter, Iter, StartValue, Operation);

        // Removing consecutive same characters from some range
        template <typename T>
        void remove_same_elems(std::vector<T> &);

        // Returns vector of pairs from two vectors same length
        template <typename T1, typename T2>
        std::vector<std::pair<T1, T2>> make_vector_of_pairs_by_two_vectors(const std::vector<T1> &,
                                                                           const std::vector<T2> &);

        // Returns vector of words in a string, except any spaces
        std::vector<std::string> split_str(const std::string &, const std::string & = " ");

        // Composing vector of string to a single string
        std::string vec_to_str(const std::vector<std::string> &);

        // Since C++20 (need std::span)
        // Composing vector of string to a single string
        std::string vec_to_str(std::span<const std::string>);

        // Returns iterator on output sequence that is one-past-last element
        // stored in the output sequence, which is contains all elements with their positions,
        // matching a predicate in a given range
        // 'first' - start iterator of the input sequence
        // 'last' - end iterator of the input sequence
        // 'dest' - start iterator of the output sequence
        template <typename InputIter, typename OutputIter, typename Predicate>
        OutputIter find_all(InputIter, InputIter,
                            OutputIter, Predicate);

        // Since C++ 20 (need std::span and <concepts>)
        // Returns sliced vector from 'first' to 'last': [first, last]
        template <typename T>
        std::vector<T> sliceVector(std::span<const T>, const std::integral auto &, const std::integral auto &);

        // Since C++ 20 (need <concepts>)
        // Slicing vector from 'first' to 'last': [first, last]
        template <typename T>
        void sliceVector(std::vector<T> &, const std::integral auto &first, const std::integral auto &);

        // Returns max subarray sum of contiguous elements in sequence
        // Solves the "Maximum subarray problem" with the "Kadane's Algorithm"
        template <typename T>
        T maxSubarraySum(std::span<const T>);

        // Returns vector of symbols in the string 'str', except any 'delim'eters
        std::vector<std::string> splitVecStringBy(std::string &, char) noexcept;

        // Returns count of unique symbols in the string 'str'
        int countOfUniqueSymbols(const std::string &);

        // Returns sum of only digits in the string 'str'
        int sumOfOnlyDigits(std::string);

        // Returns count of the first consecutive occurrences in the string
        constexpr int firstCountOfConsecutiveOccurrences(const std::string &);

        // Returns count of the first consecutive occurrences in the string
        // 'n'- is number of occurrence
        constexpr int countOfConsecutiveOccurrencesAt_n(const std::string &, size_t n = 1UL);

        // Returns maximum count of the consecutive occurrences in the string 's'
        constexpr int maxCountOfConsecutiveOccurrences(const std::string &);

        // Return vector of pairs that will store the only unique keys as a first value of pair
        // and sum of values of repeating keys as a second value of pair
        std::vector<std::pair<char, int>> compressTheVectorOfPairs(std::vector<std::string> const &);

        // Returns vector of string with all occurences
        // If you want to fill vector with all symbols which are don't match -> 'isMatch' should be -1
        std::vector<std::string> regexFindAll(std::string const &,
                                              std::string const &, int isMatch = 0);

        /// @brief Removes all punctuation signs from the string
        /// @param str string to remove punctuation
        void removePunct(std::string &str);

        /// @brief Searches occurrence: 's' == any of 'v'
        /// @param v vector of strings to search
        /// @param s string to search in vector of strings
        /// @return "true" if vector of strings contains specified string
        bool isContains(const std::vector<std::string> &v, const std::string &s);

        /// @brief Finding in the text all the words that occur in the same contexts (between the same words)
        /// @param text whole text (or any string)
        /// @return Vector of words which are occuring in the same contexts
        std::vector<std::string> getWordsInSameContexts(const std::string &text);

        /**
         * @brief Finds the most frequently element in the range
         * @tparam range range to search the most frequently element in there
         * @return The most frequently element in the range
         */
        template <typename T>
        constexpr T mostFreqElem(std::span<T const> range);

        /**
         * @brief Calculates 'k' most frequency elements in a range
         * @tparam range sequence of the elements
         * @param k count of most frequency elements to search
         * @return Vector of the most frequency elements with size 'k'
         */
        template <typename T, std::integral U>
        extern constexpr std::vector<T> kMostFreqElem(std::span<T const> range, U k);

        /**
         * @brief Searches for closest element to specified in a sequence
         * @tparam range sequence in which search
         * @tparam value value to find closest for it
         * @return Closest element to specified value
         */
        template <std::integral T>
        constexpr T findClosest(std::span<T const> range, T value);

        /**
         * @brief Calculates a common length of the all specified intervals
         * @param intervals array of intervals
         * @return Common length of the all intervals. -1 if smth wrong
         */
        int calculateIntervalsLength(std::vector<std::pair<int, int>> intervals);

        /**
         * @brief Calculates max product of 2 elems in sequence (signs are not taken in account).
         * @tparam range sequence of elements.
         * @return Max product of 2 elems. Returns min value of "unsigned long long" type if smth was wrong.
         */
        template <std::unsigned_integral T>
        unsigned long long maxPairwiseProduct(std::span<T const> range);

        /**
         * @brief Calculates max product of 3 elems in sequence (signs are taken in account).
         * @tparam range sequence of elements.
         * @return Max product of 3 elems. Returns min value of "long long" type if smth was wrong.
         */
        template <std::integral T>
        long long maxProductOf3Elems(std::span<T const> range);

        /**
         * @brief Generates new array that contains only unique elems
         * @tparam rangeA 1st range of elems
         * @tparam rangeB 2nd range of elems
         * @return Vector of an unique elems got from 2 sequences
         */
        template <std::integral T>
        constexpr std::vector<T> getUniqueElementsFromTwoSequences(std::span<T const> rangeA, std::span<T const> rangeB);

        /**
         * @brief Gathering all permutations to vector
         * @param s string
         * @return Vector that contains all permutations of string 's'
         */
        std::vector<std::string> stringPermutations(std::string s);

        /**
         * @brief Calculates 'n' elements from Tribonacci sequence by passes sequence
         * @param signature sequence of integer elements
         * @param n count of elements in the result sequence
         * @return Tribonacci sequence of 'n' size started with 'signature' elements
         */
        std::vector<int> tribonacci(std::vector<int> signature, int n);

        /**
         * @brief Calculates sum of two polynomials, assumes that coefficients in both args (polynomials)
         * are in correct order (for example, A(x) = 5x^3 + 2x^2 - 7x + 3) -> where 5 is the last index, 3 is the first.
         * @tparam a - first polynomial.
         * @tparam b - second polynomial.
         * @return C(x) - resulting polynomial in correct order (see above).
         */
        template <std::integral T>
        constexpr std::vector<T> sumOfPolynomials(std::span<T const> a, std::span<T const> b);

        /**
         * @brief Calculates sum of the matrices.
         * @tparam a - 1st matrix.
         * @tparam b - 2nd matrix.
         * @return Matrix where all elements are summarized (a + b).
         */
        template <std::integral T>
        std::vector<std::vector<T>> sumOfTheMatrices(Matrix<T> auto const &a, Matrix<T> auto const &b);

        /**
         * @brief Transposes matrix
         * @tparam T restictions: constructible, copy/move-assignable
         * @tparam matrix matrix to transpose
         * @return Transposed matrix as vector of vectors
         */
        template <typename T>
        std::vector<std::vector<T>> transposeMatrix(Matrix<T> auto const &matrix);

        /**
         * @brief Searches common prefix in sequence of strings.
         * @tparam strings sequence of strings
         * @return Common prefix in all passed strings
         */
        template <StringConvertible T>
        std::string commonPrefix(std::span<T const> strings);

        /**
         * @brief Joins passed strings with passed delimiter.
         * @param tokens strings to be combined.
         * @param delim delimiter by which they would joining.
         * @return String composed from passed range of strings with specified delimiter.
         */
        std::string join(std::span<std::string_view> tokens, std::string_view delim);
    }

    namespace big_numbers
    {
        // Calculates sum of 2 big numbers represented as array of integer
        void sum(const std::vector<int> &, const std::vector<int> &, std::vector<int> &);

        // Calculates product of 2 big numbers represented as array of integer
        void product(const std::vector<int> &, const std::vector<int> &, std::vector<int> &);

        // Returns factorial of number
        std::string factorial(int);
    }

    namespace time
    {
        // Printing current time to terminal at specified format
        void printCurTime(const StringConvertible auto &);

        // Printing duration of executing some code snippet
        // At first, where do you want to start the timer, you need to write following line:
        // auto start{std::chrono::high_resolution_clock::now()};
        // and then execute this func
        void printExecutionTime(const auto &);

        /// @brief Converts string to a formatted time (check 'time_t_to_str()' function)
        /// @param str string to convert to the time format
        /// @param format format in which will be time represented
        /// @return "time_t" time
        std::time_t str_to_time_t(std::string const &str, const char *format);

        /// @brief Converts "time_t" variable to a string (check 'str_to_time_t()' function)
        /// @param time time that will be converted
        /// @param format format in which will be time represented
        /// @return Converted time
        std::string time_t_to_str(std::time_t const &time, char const *format);

        /// @brief Generates random date of birth with age in interval [18; 100] (by default)
        /// @param lowestAge lowest age of a person - by default is 18
        /// @param highestAge highest age of a person - by default is 100
        /// @return Date of birth represented as a string with format: "dd/mm/yyyy"
        std::string generateRandomDateOfBirth(int lowestAge = 18, int highestAge = 100);
    }

    namespace files
    {
        // Returns all content from a file as a "std::string"
        std::string readFileToStr(std::string const &);

        // Returns size of the file as a "std::size_t"
        size_t getSizeOfTheFile(std::string const &);

        /// @brief Checks if file with passed filename exists
        /// @param filename name of file to do existance check
        /// @return "true" if file exists, otherwise - "false"
        bool exists(std::string const &filename);

        /**
         * @brief Collect all filenames with specified mask into a vector
         * @param path path where to search
         * @param mask file mask
         * @return Filenames with specified mask in the vector
         */
        std::vector<std::string> getFilenamesByMask(
            std::filesystem::path const &path = std::filesystem::current_path(),
            std::string const &mask = ".*\\.txt$");

        /**
         * @brief Collect all filenames with specified mask into a vector
         * @param path path where to search
         * @param mask file mask
         * @return Filenames with specified mask in the vector
         */
        std::vector<std::string> getFilenamesByMaskInDirsAndSubdirs(
            std::filesystem::path const &path = std::filesystem::current_path(),
            std::string const &mask = ".*\\.txt$");
    }
}

#include "lvt_impl.hpp"

#endif // LVT_HPP
