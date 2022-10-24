#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <vector>
#include <span>

// Returns numeric type from a string '__str'
template <typename T>
T str_to_num(const std::string &__str);

// Returns true if string is a unsigned integer number (unsigned short, unsigned int, size_t, etc.)
bool is_uint_number(const std::string &__str);

// Returns user's input as unsigned integer number
template <typename T>
T input_to_uint(const char *msg);

// Returns true if string is a signed integer number (short, int, long, etc.)
bool is_int_number(const std::string &__str);

// Returns user's input as signed integer number
template <typename T>
T input_to_int(const char *msg);

// Returns true if string is a floating number (float, double, etc.)
bool is_floating_number(const std::string &__str);

// Returns user's input as floating number
template <typename T>
T input_to_floating(const char *msg);

// Returns true if first number bigger than the second number
template <typename T>
bool is_bigger(const T &__num1, const T &__num2);

// Returns one random double number
double create_random_double(const double &__lower = 0.0, const double &__upper = 10.0);

// Returns random string
/* Hint: You must declare at the top following line:
#define __GENERATE__ALL__SYMBOLS__ for generate string consisting of all symbols
or
#define __GENERATE__ONLY__DIGITS__ for generate string consisting of only digits */
std::string generateRandomString(const size_t &__lenght);

// Turning all characters in string to lowercase
std::string str_to_lower(const char *__str);

// Makes all characters in string to uppercase
std::string str_to_upper(const std::string &__str);

// Returns array of digits in descending order
// from integer and non-negative type of number
template <typename unumeric_t>
std::vector<int> split_number_on_digits_descending(const unumeric_t &__number);

// Returns array of digits in ascending order
// from integer and non-negative type of number
template <typename unumeric_t>
std::vector<int> split_number_on_digits_ascending(const unumeric_t &__number);

// Returns result of mathematical operation 'op' that applies to each element of range
template <typename Iter, typename StartValue, typename Operation>
auto accumulateData(Iter begin, Iter end, StartValue start_value, Operation op);

// Returns 'T' as string
template <typename T>
std::string T_to_string(const T &__value);

// Returns string parameter as T
template <typename T>
T string_to_T(const std::string &__str);

// Removing consecutive same characters from some range
template <typename T>
void remove_same_elems(std::vector<T> &__range);

// Since C++20 (need std::span)
// Prints range to terminal
template <typename T>
void print_range(std::span<const T> __range);

// Prints range to terminal by iterators
template <typename Iter>
void print_range(Iter begin, Iter end);

// Removes spaces from '__str'
// Not modifies the '__str'
std::string remove_spaces_from_str(const std::string &__str);

// Removes spaces from '__str'
// Modifies the '__str'
void remove_spaces_from_str(std::string &__str);

// From C++20
// Removes spaces from '__str'
// Not modifies the '__str'
std::string remove_spaces_from_str(const std::string &__str);

// From C++20
// Removes spaces from '__str'
// Modifies the '__str'
std::string remove_spaces_from_str(std::string &__str);
