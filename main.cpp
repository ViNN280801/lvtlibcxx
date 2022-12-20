#include <iostream>
#include <tuple>

template <typename TupleType, int TupleSize>
class TuplePrintHelper
{
public:
    TuplePrintHelper(const TupleType &t)
    {
        TuplePrintHelper<TupleType, TupleSize - 1> tp{t};
        std::cout << std::get<TupleSize - 1>(t) << std::endl;
    }
};

template <typename TupleType>
class TuplePrintHelper<TupleType, 0>
{
public:
    TuplePrintHelper(const TupleType &) {}
};

template <typename T>
void printTuple(const T &t)
{
    TuplePrintHelper<T, std::tuple_size<T>::value> tph{t};
}

int main()
{
    std::tuple t{167, "Testing", false, 2.3, 53.46f};
    printTuple(t);
}