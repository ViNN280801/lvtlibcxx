#include "directed_graph.hpp"

template <typename T>
typename directed_graph<T>::nodes_container_type::iterator
directed_graph<T>::findNode(const T &__node_value)
{
    return std::find_if(std::begin(m_nodes), std::end(m_nodes), [&__node_value](const auto &node)
                        { return node.value() == __node_value; });
}

template <typename T>
typename directed_graph<T>::nodes_container_type::iterator
directed_graph<T>::findNode(const T &__node_value)
{
    return const_cast<directed_graph<T> *>(this)->findNode(__node_value);
}
