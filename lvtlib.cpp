#include "lvtlib.hpp"

namespace lvt
{
    namespace print
    {
        // Since C++20 (need std::span)
        // Prints range to terminal
        template <typename T>
        void print_range(std::span<const T> __range)
        {
            for (const auto &el : __range)
            {
                std::cout << el << ' ';
            }
            endl(std::cout);
        }

        // Prints range to terminal by iterators
        template <typename Iter>
        void print_range(Iter begin, Iter end)
        {
            for (auto iter{begin}; iter != end; ++iter)
            {
                std::cout << *iter << ' ';
            }
            endl(std::cout);
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
    }

    namespace string
    {
        namespace convert
        {
            // Returns string parameter as T
            template <typename T>
            T string_to_T(const std::string &__str)
            {
                T value;
                std::istringstream iss(__str);
                iss >> value;
                return value;
            }
        }

        namespace checkings
        {
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
        }

        namespace modifying
        {
            // Turning all characters in string to lowercase
            std::string str_to_lower(const std::string &__str)
            {
                std::string str{__str};
                std::transform(std::begin(str), std::end(str), std::begin(str), ::tolower);
                return str;
            }

            // Makes all characters in string to uppercase
            std::string str_to_upper(const std::string &__str)
            {
                std::string str{__str};
                std::transform(std::begin(str), std::end(str), std::begin(str), ::toupper);
                return str;
            }

            // Returns string '__str' without vowels
            std::string remove_vowels_(const std::string &__str)
            {
                std::string str(__str);
                str.erase(std::remove_if(std::begin(str), std::end(str), [](const char &ch)
                                         { return lvt::algorithm::is_vowel(ch); }),
                          std::cend(str));
                return str;
            }

            // Since C++20 (need std::erase_if())
            // Returns string '__str' without vowels
            std::string remove_vowels_cxx_20(const std::string &__str)
            {
                std::string str(__str);
                std::erase_if(str, [](const char &ch)
                              { return lvt::algorithm::is_vowel(ch); });
                return str;
            }

            // Returns string '__str' without vowels (need std::regex)
            std::string remove_vowels_regex(const std::string &__str)
            {
                std::string str(__str);
                std::regex vowels("[aeiouAEOIOU]");
                return std::regex_replace(str, vowels, "");
            }
        }
    }

    namespace input
    {
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
                if (lvt::string::checkings::is_uint_number(users_input))
                    break;
                // Else: print message and back to the begininng of 'while' loop
                else
                    std::cout << "You entered not an unsigned integer number. Try again.\n";
            }

            // Converting user's string to numeric type to return it as a result
            T num{str_to_num<T>(users_input)};

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
                if (lvt::string::checkings::is_int_number(users_input))
                    break;
                // Else: print message and back to the begininng of 'while' loop
                else
                    std::cout << "You entered not an signed integer number. Try again.\n";
            }

            // Converting user's string to numeric type to return it as a result
            T num{str_to_num<T>(users_input)};

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
                if (lvt::string::checkings::is_floating_number(users_input))
                    break;
                // Else: print message and back to the begininng of 'while' loop
                else
                    std::cout << "You entered not an floating number. Try again.\n";
            }

            // Converting user's string to numeric type to return it as a result
            T num{str_to_num<T>(users_input)};

            // Returning converted user's inputted value to 'T' type
            return num;
        }
    }

    namespace random
    {
        // Returns one random double number
        double create_random_double(const double &__lower, const double &__upper)
        {
            return __lower + (static_cast<double>(rand()) / RAND_MAX) * (__upper - __lower);
        }

        // Returns random string
        /* Hint: You must declare at the top following line:
            #define __GENERATE__ALL__SYMBOLS__ for generate string consisting of all symbols
            or
            #define __GENERATE__ONLY__DIGITS__ for generate string consisting of only digits */
        std::string generateRandomString(const size_t &__lenght)
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
    }

    namespace algorithm
    {
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

        // Returns "true" if '__ch' is vowel, otherwise - "false"
        bool is_vowel(const char &__ch)
        {
            return (__ch == 'a' || __ch == 'e' || __ch == 'i' || __ch == 'o' ||
                    __ch == 'u' || __ch == 'A' || __ch == 'E' ||
                    __ch == 'I' || __ch == 'O' || __ch == 'U')
                       ? true
                       : false;
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

        // Returns 'T' as string
        template <typename T>
        std::string T_to_string(const T &__value)
        {
            std::ostringstream oss;
            oss << __value;
            return oss.str();
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
    }
}
