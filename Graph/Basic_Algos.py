import copy

class Graph:
	def __init__(self):
		self.vertices = {}
		self.invVertices = []
		self.adjList = []
		self.size = 0

	def insert_node(self, name):
		self.invVertices.append(name)
		self.vertices[name] = self.size
		self.adjList.append([])
		self.size += 1

	def insert_edge(self, src, dest, weight = 1):
		self.adjList[self.vertices[src]].append((self.vertices[dest], weight))

	def bfs(self, source):
		source = self.vertices[source]
		visit = [True for i in xrange(self.size)]
		queue = [source]
		visit[source] = False
		pi = {source : source}

		while len(queue) != 0:
			c = queue.pop()
			print "Node: ", self.invVertices[c], "\t Pi(", self.invVertices[c], "): ", self.invVertices[pi[c]]

			for n,w in self.adjList[c]:
				if visit[n]:
					queue.insert(0, n)
					pi[n] = c
					visit[n] = False

	def dfs_iterative(self, source):
		source = self.vertices[source]
		visit = [True for i in xrange(self.size)]
		stack = [source]
		pi = {source : source}

		while len(stack) != 0:
			c = stack.pop()

			if visit[c]:
				print "Node: ", self.invVertices[c], "\t Pi(", self.invVertices[c], "): ", self.invVertices[pi[c]]

				visit[c] = False

			for n,w in self.adjList[c]:
				if visit[n]:
					stack.append(n)
					pi[n] = c

	def vertices_decreasing_finish_time_visit(self, root, visit, sortedVertices):
		visit[root] = False

		for node, wt in self.adjList[root]:
			if visit[node]:
				self.vertices_decreasing_finish_time_visit(node, visit, sortedVertices)

		sortedVertices.insert(0, root)

	def vertices_decreasing_finish_time(self):
		visit = [True for i in xrange(self.size)]
		sortedVertices = []

		for i in xrange(self.size):
			if visit[i]:
				self.vertices_decreasing_finish_time_visit(i, visit, sortedVertices)

		return sortedVertices

	def get_transpose(self):
		transpose = copy.deepcopy(self)
		transpose.adjList = [[] for i in xrange(transpose.size)]

		for i in xrange(self.size):
			for node, wt in self.adjList[i]:
				transpose.adjList[node].append((i, wt))

		return transpose

	def strongly_connected_components(self):
		transpose = self.get_transpose()
		visit = [True for i in xrange(self.size)]
		scc = []

		for i in self.vertices_decreasing_finish_time():
			if visit[i]:
				l = []
				transpose.vertices_decreasing_finish_time_visit(i, visit, l)
				scc.append(l)

		return scc

	def dijkstra(self, rt):
		root = self.vertices[rt]
		INF = float('inf')
		m = Heap(size = self.size, inf = INF)
		dist = [INF for i in xrange(self.size)]
		pi = [0 for i in xrange(self.size)]

		m.update(root, 0)
		pi[root] = root
		dist[root] = 0

		for i in xrange(self.size):
			root = m.extract_top()

			if dist[root] == INF:
				break

			for node, wt in self.adjList[root]:
				if dist[root] + wt < dist[node]:
					dist[node] = dist[root] + wt
					m.update(node, dist[node])
					pi[node] = root

		for i in xrange(self.size):
			if dist[i] != INF:
				print "Node: ", self.invVertices[i],"\tDistance: ",dist[i],"\tPi(",self.invVertices[i],"): ",self.invVertices[pi[i]]

class UndirectedGraph(Graph):
	def __init__(self):
		Graph.__init__(self)

	def insert_edge(self, node1, node2, wt = 1):
		Graph.insert_edge(self, node1, node2, wt)
		Graph.insert_edge(self, node2, node1, wt)

	def span_tree_prim(self, rt, isMin = True):
		root = self.vertices[rt]
		INF = float('inf') * (1 if isMin else -1)
		m = Heap(size = self.size, inf = INF, isMin = isMin)
		dist = [INF for i in xrange(self.size)]
		pi = [0 for i in xrange(self.size)]
		visit = [True for i in xrange(self.size)]

		m.update(root, 0)
		pi[root] = root
		dist[root] = 0

		for i in xrange(self.size):
			root = m.extract_top()
			visit[root] = False

			if dist[root] == INF:
				break

			for node, wt in self.adjList[root]:
				if visit[node] and (wt < dist[node] if isMin else wt > dist[node]):
					dist[node] = wt
					m.update(node, dist[node])
					pi[node] = root

		for i in xrange(self.size):
			if dist[i] != INF:
				print "Node: ", self.invVertices[i],"\tEdge Weight: ",dist[i],"\tPi(",self.invVertices[i],"): ",self.invVertices[pi[i]]

	def span_forest_kruskal(self, isMin = True):
		edgeList = []

		for i in xrange(self.size):
			for node, wt in self.adjList[i]:
				if node >= i:
					edgeList.append((i, node, wt))

		edgeList.sort(key = lambda x: x[2], reverse = not isMin)

		spanForest = [[] for i in xrange(self.size)]
		getComp = [i for i in xrange(self.size)]
		sizeComp = [1 for i in xrange(self.size)]

		for curredge in edgeList:
			if getComp[curredge[0]] != getComp[curredge[1]]:
				minSizeComp = getComp[curredge[0]]
				maxSizeComp = getComp[curredge[1]]
				if sizeComp[minSizeComp] > sizeComp[maxSizeComp]:
					minSizeComp, maxSizeComp = maxSizeComp, minSizeComp

				for edge in spanForest[minSizeComp]:
					getComp[edge[0]] = maxSizeComp
					getComp[edge[1]] = maxSizeComp

				sizeComp[maxSizeComp] += sizeComp[minSizeComp]
				sizeComp[minSizeComp] = 0

				spanForest[maxSizeComp].append(curredge)
				getComp[curredge[0]] = maxSizeComp
				getComp[curredge[1]] = maxSizeComp

				spanForest[minSizeComp] = []

		for tree in spanForest:
			if tree:
				print "Tree:"
				for edge in tree:
					print "Node 1: ",self.invVertices[edge[0]],"\tNode 2: ",self.invVertices[edge[1]],"\tEdge Weight: ",edge[2]

class Heap:
	@staticmethod
	def parent(n):
		return (n-1)/2

	@staticmethod
	def left(n):
		return 2*n + 1

	@staticmethod
	def right(n):
		return 2*n + 2

	def compare(self, a, b):
		return (a < b if self.isMin else a > b)

	def swap(self, i, j):
		self.pos[self.heap[i][0]] = j
		self.pos[self.heap[j][0]] = i
		self.heap[i], self.heap[j] = self.heap[j], self.heap[i]

	def __init__(self, size, inf, isMin = True):
		self.pos = [i for i in xrange(size)]
		self.heap = [[i, inf] for i in xrange(size)]
		self.size = size
		self.isMin = isMin

	def update(self, i, newVal):
		if self.compare(self.heap[self.pos[i]][1], newVal):
			self.heap[self.pos[i]][1] = newVal
			self.top_down_heapify(self.pos[i])

		else:
			self.heap[self.pos[i]][1] = newVal
			self.bottom_up_heapify(self.pos[i])

	def extract_top(self):
		retVal = self.heap[0][0]
		self.size -= 1
		self.swap(0, self.size)
		self.heap.pop()
		self.top_down_heapify(0)
		return retVal

	def top_down_heapify(self, i):
		l = Heap.left(i)
		r = Heap.right(i)
		j = i

		while r < self.size:
			j = l if self.compare(self.heap[l][1], self.heap[r][1]) else r

			if self.compare(self.heap[i][1], self.heap[j][1]):
				break

			else:
				self.swap(i, j)
				i = j
				l = Heap.left(i)
				r = Heap.right(i)

		if l == self.size - 1 and self.compare(self.heap[l][1], self.heap[j][1]):
			self.swap(l, j)

	def bottom_up_heapify(self, i):
		p = Heap.parent(i)
		while(p >= 0):
			if self.compare(self.heap[i][1], self.heap[p][1]):
				self.swap(i, p)
				i = p
				p = Heap.parent(i)

			else:
				break

if __name__ == "__main__":
	a = UndirectedGraph()

	a.insert_node(1)
	a.insert_node('B')
	a.insert_node('C')
	a.insert_node('D')
	a.insert_node('E')
	a.insert_node('F')
	a.insert_node('G')
	a.insert_node('H')
	a.insert_node('I')

	a.insert_edge('A', 'B', 4)
	a.insert_edge('B', 'C')
	a.insert_edge('D', 'B', 3)
	a.insert_edge('E', 'D', 7)
	a.insert_edge('E', 'C', 8)
	a.insert_edge('C', 'F')
	a.insert_edge('E', 'A', 3)
	a.insert_edge('G', 'H', 5)
	a.insert_edge('G', 'I', 10)
	a.insert_edge('H', 'I', 4)

	print "BFS:"
	a.bfs('A')

	print "\nDFS:"
	a.dfs_iterative('A')

	print "\nDijkstra:"
	a.dijkstra('A')

	print "\nMinimum Span Tree Prim's:"
	a.span_tree_prim('A')

	print "\nMaximum Span Tree Prim's:"
	a.span_tree_prim('A', False)

	print "\nMinimum Span Forest Kruskal's:"
	a.span_forest_kruskal()

	print "\nMaximum Span Tree Kruskal's:"
	a.span_forest_kruskal(False)

	print "\nStrongly Connected Components:"
	print a.strongly_connected_components()
