from collections import deque

graph = {
    'A': ['B', 'C'],
    'B': ['A', 'D', 'E'],
    'C': ['A', 'F'],
    'D': ['B'],
    'E': ['B', 'F'],
    'F': ['C', 'E']
}

start = 'A'
end =  'F'

def redo_path():
    


def BFS(graph, start, end):
    queue = deque([start])
    parents = {start:None}

    while queue:
        actual_node = queue.poplef()
        if(actual_node == end):
            return redo_path(parents, start, end)

        for neighbor in graph[actual_node]:
            if neighbor not in parents:
                parents[neighbor] = actual_node
                queue.append(neighbor)

    return None