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

namespace lvt
{
    namespace print
    {
        // Since C++20 (need std::span)
        // Prints range to terminal
        template <typename T>
        void print_range(std::span<const T>);

        // Prints range to terminal by iterators
        template <typename Iter>
        void print_range(Iter, Iter);

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

    namespace string
    {
        namespace convert
        {
            // Returns string parameter as T
            template <typename T>
            T string_to_T(const std::string &);
        }

        namespace checkings
        {
            // Returns true if string is a unsigned integer number (unsigned short, unsigned int, size_t, etc.)
            bool is_uint_number(const std::string &);

            // Returns true if string is a signed integer number (short, int, long, etc.)
            bool is_int_number(const std::string &);

            // Returns true if string is a floating number (float, double, etc.)
            bool is_floating_number(const std::string &);
        }

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
    }

    namespace algorithm
    {
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

        // Returns 'T' as string
        template <typename T>
        std::string T_to_string(const T &);

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
        int countOfUniqueSymbols(const std::string &str);

        // Returns sum of only digits in the string 'str'
        int sumOfOnlyDigits(std::string str);
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
}
