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

#include "lvt_impl.hpp"

using namespace std::chrono_literals;

namespace lvt
{
    // Concept that specifies all types that can be convert to "std::string_view" type
    // For example, "char", "const char *", "std::string", etc.
    template <typename T>
    concept String = std::is_convertible_v<T, std::string_view>;

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
        bool is_vowel(const char &);

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
        std::vector<std::vector<T>> arrToMatrix(std::vector<T> const &, size_t const &, size_t const &);
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
        std::string generateRandomString(const size_t &);

        // Returns random vector filled with integer numbers
        // 'vecSize' - size of the vector
        // 'from' - lower number
        // 'to' - higher number to generate
        std::vector<int> generateRandomIntVector(size_t const &vecSize = 10UL, int const &from = -50, int const &to = 50);

        // Returns matrix of integers that is filled with random numbers
        // Gets rows as a first parameter and columns as a second
        // Third param - offset, fourth - range
        std::vector<std::vector<int>> generateRandomIntMatrix(size_t const &rows, size_t const &cols,
                                                              int const &offset = 1, int const &range = 100);
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
        std::vector<std::string> splitVecStringBy(std::string &, const char &) noexcept;

        // Returns count of unique symbols in the string 'str'
        int countOfUniqueSymbols(const std::string &);

        // Returns sum of only digits in the string 'str'
        int sumOfOnlyDigits(std::string);

        // Returns count of the first consecutive occurrences in the string
        constexpr int firstCountOfConsecutiveOccurrences(const std::string &);

        // Returns count of the first consecutive occurrences in the string
        // 'n'- is number of occurrence
        constexpr int countOfConsecutiveOccurrencesAt_n(const std::string &, const size_t &n = 1UL);

        // Returns maximum count of the consecutive occurrences in the string 's'
        constexpr int maxCountOfConsecutiveOccurrences(const std::string &);

        // Return vector of pairs that will store the only unique keys as a first value of pair
        // and sum of values of repeating keys as a second value of pair
        std::vector<std::pair<char, int>> compressTheVectorOfPairs(std::vector<std::string> const &);

        // Returns vector of string with all occurences
        // If you want to fill vector with all symbols which are don't match -> 'isMatch' should be -1
        std::vector<std::string> regexFindAll(std::string const &,
                                              std::string const &, int const &isMatch = 0);
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
        void printCurTime(const String auto &);

        // Printing duration of executing some code snippet
        // At first, where do you want to start the timer, you need to write following line:
        // auto start{std::chrono::high_resolution_clock::now()};
        // and then execute this func
        void printExecutionTime(const auto &);
    }

    namespace files
    {
        // Returns all content from a file as a "std::string"
        std::string readFileToStr(std::string const &);

        // Returns size of the file as a "std::size_t"
        size_t getSizeOfTheFile(std::string const &);
    }
}

#endif // LVT_HPP
