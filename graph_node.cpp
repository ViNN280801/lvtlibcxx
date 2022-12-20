#include "graph_node.hpp"

namespace details
{
    template <typename T>
    graph_node<T>::graph_node(directed_graph<T> *__graph, const T &__t) : m_graph{__graph}, m_data{__t} {}

    template <typename T>
    graph_node<T>::graph_node(directed_graph<T> *__graph, T &&__t) : m_graph{__graph}, m_data{std::move(__t)} {}
}