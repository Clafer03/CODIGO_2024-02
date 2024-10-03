mapa = {
    'A': [('B', 5), ('C', 2)],
    'B': [('D', 4), ('E', 3)],
    'C': [('F', 6)],
    'D': [('G', 7)],
    'E': [('G', 8), ('H', 2)],
    'F': [('H', 3)],
    'G': [('I', 1)],
    'H': [('I', 5)],
    'I': []
}

heuristica = {
    'A': 10,
    'B': 8,
    'C': 7,
    'D': 6,
    'E': 5,
    'F': 4,
    'G': 3,
    'H': 6,
    'I': 0
}

visited = []
queue = []
def BFS(visited, mapa, start_node):

    visited.append(start_node)
    queue.append(start_node)

    while queue:
        m = queue.pop(0) # quita la primera posición para que los demas elementos en la cola puedan seguir
        print(m, end=" ")
        for neighbour, _ in mapa[m]: # mapea solo los vecinos sin considerar las distancias (..., _ in ...)
            if neighbour not in visited:
                visited.append(neighbour)
                queue.append(neighbour)

BFS(visited, mapa, 'A') 