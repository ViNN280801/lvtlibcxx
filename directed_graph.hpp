export module directed_graph;

#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

export template <typename T>
class directed_graph
{
private:
    using nodes_container_type = std::vector<details::graph_node<T>>;
    nodes_container_type m_nodes;

    typename nodes_container_type::iterator findNode(const T &__node_value);
    typename nodes_container_type::const_iterator findNode(const T &__node_value) const;

public:
    // Returns "true" if a new node with given value has been added to
    // the graph, and "false" if there was already a node with the given value.
    bool is_inserted(const T &__node_value);

    // Returns "true" if a new node with given value has been added to
    // the graph, and "false" if there was already a node with the given value.
    bool is_inserted(T &&__node_value);

    // Returns "true" if the given node value was erased, otherwise - "false"
    bool is_erased(const T &__node_value);

    // Returns "true" if the edge was successfully created, otherwise - "false"
    bool is_edge_created(const T &__from_node_value, const T &__to_node_value);

    // Returns "true" if the edge was successfully erased, otherwise - "false"
    bool is_edge_erased(const T &__from_node_value, const T &__to_node_value);

    // Removes all nodes from the graph
    void clear() noexcept;

    // Returns a reference to the node with given index
    // No bounds checking is done
    T &operator[](size_t __index);
    const T &operator[](size_t __index) const;

    // Two directed graphs are equal if they have the same nodes and edges
    // The order in which the nodes and edges have been added does not
    // affect equality
    bool operator==(const directed_graph &__rhs) const;

    // Two directed graphs are equal if they have the same nodes and edges
    // The order in which the nodes and edges have been added does not
    // affect equality
    bool operator!=(const directed_graph &__rhs) const;

    // Swaps all nodes between this graph and the given graph
    void swap(directed_graph &__other_graph) noexcept;

    // Returns the number of nodes in the graph.
    [[nodiscard]] size_t size() const noexcept;

    // Returns a set with the adjacent nodes of a given node
    // If the given node does not exist, an empty set is returned
    [[nodiscard]] std::set<T> get_adjacent_nodes_values(const T &__node_value) const;
};
