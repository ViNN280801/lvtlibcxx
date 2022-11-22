#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <regex>
#include <span>
#include <tuple>

namespace lvt
{
    namespace print
    {
        // Since C++20 (need std::span)
        // Prints range to terminal
        template <typename T>
        void print_range(std::span<const T> __range);

        // Prints range to terminal by iterators
        template <typename Iter>
        void print_range(Iter begin, Iter end);

        // Prints vector of pairs to terminal
        template <typename T1, typename T2>
        void print_pair_vec(const std::vector<std::pair<T1, T2>> &__vec);

        // Prints dictionary to terminal (need std::map)
        template <typename T1, typename T2>
        void print_dictionary(const std::map<T1, T2> &__dictionary);

        namespace print_tuple
        {
            template <typename TupleType, int TupleSize>
            class TuplePrintHelper
            {
            public:
                TuplePrintHelper(const TupleType &t);
            };

            template <typename TupleType>
            class TuplePrintHelper<TupleType, 0>
            {
            public:
                TuplePrintHelper(const TupleType &) {}
            };

            template <typename T>
            void printTuple(const T &t);
        }
    }

    namespace string
    {
        namespace convert
        {
            // Returns string parameter as T
            template <typename T>
            T string_to_T(const std::string &__str);
        }

        namespace chekings
        {
            // Returns true if string is a unsigned integer number (unsigned short, unsigned int, size_t, etc.)
            bool is_uint_number(const std::string &__str);

            // Returns true if string is a signed integer number (short, int, long, etc.)
            bool is_int_number(const std::string &__str);

            // Returns true if string is a floating number (float, double, etc.)
            bool is_floating_number(const std::string &__str);
        }

        namespace modifying
        {
            // Turning all characters in string to lowercase
            std::string str_to_lower(const std::string &__str);

            // Makes all characters in string to uppercase
            std::string str_to_upper(const std::string &__str);

            // Returns string '__str' without vowels
            std::string remove_vowels(const std::string &__str);

            // Since C++20 (need std::erase_if())
            // Returns string '__str' without vowels
            std::string remove_vowels_cxx_20(const std::string &__str);

            // Returns string '__str' without vowels (need std::regex)
            std::string remove_vowels_regex(const std::string &__str);

            // Returns string '__str' without vowels
            void remove_vowels(std::string &__str);

            // Since C++20 (need std::erase_if())
            // Returns string '__str' without vowels
            void remove_vowels_cxx_20(std::string &__str);

            // Returns string '__str' without vowels (need std::regex)
            void remove_vowels_regex(std::string &__str);

            // Removing consecutive same characters from some range
            std::string remove_consecutive_spaces(const std::string &__str);

            // Removing consecutive same characters from some range
            void remove_consecutive_spaces(std::string &__str);
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
        std::string generateRandomString(const size_t &__lenght);
    }

    namespace algorithm
    {
        // Returns true if both are equals
        template <typename T>
        bool is_equal(const T &__num1, const T &__num2);

        // Returns true if first lower than the second
        template <typename T>
        bool is_lower(const T &__num1, const T &__num2);

        // Returns true if first bigger than the second
        template <typename T>
        bool is_bigger(const T &__num1, const T &__num2);

        // Returns "true" if '__ch' is vowel, otherwise - "false"
        bool is_vowel(const char &__ch);

        // Returns array of digits in descending order
        // from integer and non-negative type of number
        template <typename unumeric_t>
        std::vector<int> split_number_on_digits(const unumeric_t &__number);

        // Returns result of mathematical operation 'op' that applies to each element of range
        template <typename Iter, typename StartValue, typename Operation>
        auto accumulateData(Iter begin, Iter end, StartValue start_value, Operation op);

        // Returns 'T' as string
        template <typename T>
        std::string T_to_string(const T &__value);

        // Removing consecutive same characters from some range
        template <typename T>
        void remove_same_elems(std::vector<T> &__range);

        // Returns vector of pairs from two vectors same length
        template <typename T1, typename T2>
        std::vector<std::pair<T1, T2>> make_vector_of_pairs_by_two_vectors(const std::vector<T1> &__vec1,
                                                                           const std::vector<T2> &__vec2);

        // Returns vector of words in a string, except any spaces
        std::vector<std::string> split_str(const std::string &__str, const std::string &__delimiter = " ");

        // Composing vector of string to a single string
        std::string vec_to_str(const std::vector<std::string> &__vec);

        // Since C++20 (need std::span)
        // Composing vector of string to a single string
        std::string vec_to_str(std::span<const std::string> __vec);

        // Returns iterator on output sequence that is one-past-last element
        // stored in the output sequence, which is contains all elements with their positions,
        // matching a predicate in a given range
        // 'first' - start iterator of the input sequence
        // 'last' - end iterator of the input sequence
        // 'dest' - start iterator of the output sequence
        template <typename InputIter, typename OutputIter, typename Predicate>
        OutputIter find_all(InputIter first, InputIter last,
                            OutputIter dest, Predicate pred);
    }
}
