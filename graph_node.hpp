module directed_graph:node;

#include "directed_graph.hpp"

namespace details
{
    template <typename T>
    class graph_node
    {
    private:
        friend class directed_graph<T>;

        // A pointer to the graph this node is in
        directed_graph<T> *m_graph;

        // Type to store the adjacency list
        using adjacency_list_type = std::set<size_t>;

        // Retutns a reference to the adjacency list
        [[nodiscard]] inline adjacency_list_type &get_adjacent_nodes_indices() { return m_adjacent_node_indices; }
        [[nodiscard]] inline const adjacency_list_type &get_adjacent_nodes_indices() const { return m_adjacent_node_indices; }

        // Data that contains in node
        T m_data;

        // Set of adjacent indeces of node
        adjacency_list_type m_adjacent_node_indices;

    public:
        // Constructs a 'graph_node' for a given value
        graph_node(directed_graph<T> *__graph, const T &__t);
        graph_node(directed_graph<T> *__graph, T &&__t);

        // Returns a reference to the stored value
        [[nodiscard]] inline T &value() noexcept { return m_data; }
        [[nodiscard]] inline const T &value() noexcept { return m_data; }

        // C++20 deafult operator==
        bool operator==(const graph_node &) const = default;
    };
}
