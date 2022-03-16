import networkx as nx
import matplotlib.pyplot as plt
import csv
import matplotlib


# matplotlib.use('qt')


def make_hamilton(n):
    g = nx.Graph()
    g.add_nodes_from(list(range(n)))
    g.add_edges_from([(list(g.nodes)[i], list(g.nodes)[(i + 1) % len(g.nodes)]) for i in range(len(g.nodes))])
    print(g.nodes())
    print(g.edges())
    nx.draw(g, with_labels=True, pos=nx.circular_layout(g))
    plt.show()


success = 'data/Hill_Climber/TEST_g=9_n=40/solution_g=9_n=40_1.txt'
debug = 'edge_removal_debug'


def load_graph_from_gml(fname):
    return nx.read_gml(fname)


def save_graph_gml(G, fname):
    nx.write_gml(G, fname)


def read_graph_prom_txt(path):
    return nx.read_adjlist(path, create_using=nx.DiGraph(), nodetype=int).to_undirected()


def draw_graph(G):
    nx.draw(G, with_labels=True, pos=nx.planar_layout(G))
    plt.show()


def save_cycles_csv(cycles: list[list], path: str):
    with open(path, "w") as f:
        wr = csv.writer(f)
        wr.writerows(cycles)


def graph_compare(G1: nx.Graph, G2: nx.Graph) -> bool:
    return nx.is_isomorphic(G1, G2)


def load_cycles_from_csv(path='data/Hill_Climber/solution_g=9_n=40_1_cycles.csv'):
    cycles = list()
    with open(path, "r") as file:
        reader = csv.reader(file)
        for row in reader:
            if len(row) != 0:
                cycles.append([int(i) for i in row])
    return cycles


def BaseDfs(G):
    stack = list()
    tree = list()
    visited = [False] * G.number_of_nodes()

    root = list(G.nodes())[0]
    stack.append(root)
    tree.append(root)

    while len(stack) != 0:
        u = stack.pop()
        if not visited[u]:
            visited[u] = True
            for v in G.neighbors(u):
                tree.append(v)
                stack.append(v)
    return tree


def find_all_cycles(G, source=None):
    """forked from networkx dfs_edges function. Assumes nodes are integers, or at least
    types which work with min() and > .
    NP-COMPLETE"""
    if source is None:
        # produce edges for all components
        nodes = [list(i)[0] for i in nx.connected_components(G)]
    else:
        # produce edges for components with source
        nodes = [source]
    # extra variables for cycle detection:
    cycle_stack = []
    output_cycles = set()

    def get_hashable_cycle(cycle):
        """cycle as a tuple in a deterministic order."""
        m = min(cycle)
        mi = cycle.index(m)
        mi_plus_1 = mi + 1 if mi < len(cycle) - 1 else 0
        if cycle[mi - 1] > cycle[mi_plus_1]:
            result = cycle[mi:] + cycle[:mi]
        else:
            result = list(reversed(cycle[:mi_plus_1])) + list(reversed(cycle[mi_plus_1:]))
        return tuple(result)

    for start in nodes:
        if start in cycle_stack:
            continue
        cycle_stack.append(start)

        stack = [(start, iter(G[start]))]
        while stack:
            parent, children = stack[-1]
            try:
                child = next(children)

                if child not in cycle_stack:
                    cycle_stack.append(child)
                    stack.append((child, iter(G[child])))
                else:
                    i = cycle_stack.index(child)
                    if i < len(cycle_stack) - 2:
                        output_cycles.add(get_hashable_cycle(cycle_stack[i:]))
            except StopIteration:
                stack.pop()
                cycle_stack.pop()

    return [list(i) for i in output_cycles]


def get_smallest_cycle(cycles: list[list]) -> list:
    curr_len = len(cycles[0])
    curr_idx = 0
    for idx, cycle in enumerate(cycles):
        if len(cycle) < curr_len:
            curr_len = len(cycle)
            curr_idx = idx
    return cycles[curr_idx]


def rout_to_edges(route: list) -> list[tuple]:
    return [(route[n], route[(n + 1) % len(route)]) for n in range(len(route))]


def draw_cycle_on_graph(G: nx.Graph, edges: list):
    edge_color_list = ["grey"] * len(G.edges)
    for i, edge in enumerate(G.edges()):
        if edge in edges or (edge[1], edge[0]) in edges:
            edge_color_list[i] = 'red'
    # pos = nx.circular_layout(G)
    plt.title(f'g = 9 n = 40 smallest cycles in red len(C) ={len(edges) + 1}')
    nx.draw(G, with_labels=True, edge_color=edge_color_list)

    plt.show()


def find_short_cycles(cycles: list, g: int) -> list[list]:
    short_cycles = list()
    for cycle in cycles:
        if len(cycle) < g - 1:
            short_cycles.append(cycle)
            print(cycle)
    return short_cycles


G = read_graph_prom_txt('data/Hill_ClimberEvenOdd/solution_g=4_n=20_1.txt')
# save_graph_gml(G, 'data/Hill_Climber/TEST_g=5_n=10-10/solution_g=5_n=10_1.gml')
# G = load_graph_from_gml('data/Hill_Climber/TEST_g=5_n=10-10/solution_g=5_n=10_1.gml')
# draw_graph(G)

# G = read_graph_prom_txt('data/Hill_Climber/TEST_g=5_n=10-10/solution_g=5_n=10_1.txt')
# save_graph_gml(G, 'data/Hill_Climber/TEST_g=5_n=10-10/solution_g=5_n=10_1.gml')
# G = load_graph_from_gml('data/Hill_Climber/TEST_g=5_n=10-10/solution_g=5_n=10_1.gml')
# draw_graph(G)
# cycles = find_short_cycles(find_all_cycles(G), 5)
# cycles = find_all_cycles(G)
# save_cycles_csv(cycles, 'data/Hill_Climber/TEST_g=5_n=50/solution_g=5_n=50_1_cycles.csv')
# short_cycles = find_short_cycles(cycles, 9)
# save_cycles_csv(short_cycles, 'data/Hill_Climber/TEST_g=5_n=50/solution_g=5_n=50_1_short_cycles.csv')

# short_cycles = find_short_cycles(
#     load_cycles_from_csv('data/Hill_Climber/TEST_g=5_n=20-60/solution_g=5_n=30_1_cycles.csv') ,g=5)
# print(short_cycles)

# plt.show()
