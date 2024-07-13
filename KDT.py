import math
from typing import List, Tuple

class KDTreeNode:
    def __init__(self, point, left=None, right=None):
        self.point = point
        self.left = left
        self.right = right

class KDTree:
    def __init__(self, k):
        self.k = k
        self.root = None

    def insert(self, root, point, depth=0):
        if root is None:
            return KDTreeNode(point)

        cd = depth % self.k

        if point[cd] < root.point[cd]:
            root.left = self.insert(root.left, point, depth + 1)
        else:
            root.right = self.insert(root.right, point, depth + 1)

        return root

    def delete(self, root, point, depth=0):
        if root is None:
            return None

        cd = depth % self.k

        if root.point == point:
            if root.right:
                min_node = self.find_min(root.right, cd, depth + 1)
                root.point = min_node.point
                root.right = self.delete(root.right, min_node.point, depth + 1)
            elif root.left:
                min_node = self.find_min(root.left, cd, depth + 1)
                root.point = min_node.point
                root.right = self.delete(root.left, min_node.point, depth + 1)
                root.left = None
            else:
                return None
        elif point[cd] < root.point[cd]:
            root.left = self.delete(root.left, point, depth + 1)
        else:
            root.right = self.delete(root.right, point, depth + 1)

        return root

    def find_min(self, root, d, depth=0):
        if root is None:
            return None

        cd = depth % self.k

        if cd == d:
            if root.left is None:
                return root
            return self.find_min(root.left, d, depth + 1)

        left_min = self.find_min(root.left, d, depth + 1)
        right_min = self.find_min(root.right, d, depth + 1)

        return min((root, left_min, right_min), key=lambda x: x.point[d] if x else float('inf'))

    def range_search(self, root, point, range, depth=0):
        if root is None:
            return []

        cd = depth % self.k
        in_range = all(abs(root.point[i] - point[i]) <= range for i in range(self.k))

        results = []
        if in_range:
            results.append(root.point)

        if point[cd] - range <= root.point[cd]:
            results.extend(self.range_search(root.left, point, range, depth + 1))
        if point[cd] + range >= root.point[cd]:
            results.extend(self.range_search(root.right, point, range, depth + 1))

        return results

    def nearest_neighbor(self, root, point, depth=0):
        if root is None:
            return None

        self.best = None
        self.best_dist = float('inf')
        self._nearest_neighbor(root, point, depth)
        return self.best

    def _nearest_neighbor(self, root, point, depth=0):
        if root is None:
            return

        cd = depth % self.k
        current_dist = self.distance(point, root.point)

        if current_dist < self.best_dist:
            self.best_dist = current_dist
            self.best = root.point

        if point[cd] < root.point[cd]:
            self._nearest_neighbor(root.left, point, depth + 1)
            if abs(point[cd] - root.point[cd]) < self.best_dist:
                self._nearest_neighbor(root.right, point, depth + 1)
        else:
            self._nearest_neighbor(root.right, point, depth + 1)
            if abs(point[cd] - root.point[cd]) < self.best_dist:
                self._nearest_neighbor(root.left, point, depth + 1)

    def distance(self, point1, point2):
        return math.sqrt(sum((x - y) ** 2 for x, y in zip(point1, point2)))

    def insert_point(self, point):
        self.root = self.insert(self.root, point)

    def delete_point(self, point):
        self.root = self.delete(self.root, point)

    def range_search_points(self, point, range):
        return self.range_search(self.root, point, range)

    def nearest_neighbor_point(self, point):
        return self.nearest_neighbor(self.root, point)

# Example usage
if __name__ == "__main__":
    kdtree = KDTree(k=2)
    points = [(2, 3), (5, 4), (9, 6), (4, 7), (8, 1), (7, 2)]

    for point in points:
        kdtree.insert_point(point)

    print("Range search results:", kdtree.range_search_points((5, 5), 3))
    print("Nearest neighbor:", kdtree.nearest_neighbor_point((5, 5)))

    kdtree.delete_point((5, 4))
    print("After deletion, nearest neighbor:", kdtree.nearest_neighbor_point((5, 5)))
