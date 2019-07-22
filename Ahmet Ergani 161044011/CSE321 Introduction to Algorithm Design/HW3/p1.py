import xlrd

def readXLS():
    graph = {}
    workbook = xlrd.open_workbook('Graph_data.xls')
    sheet = workbook.sheet_by_name('Sheet1')
    a = 3
    while 1:
        if a == 20:
            print(graph)
            return graph
        if graph.keys().__contains__(sheet.cell(a, 0).value):
            graph[int(sheet.cell(a, 0).value)].add(int(sheet.cell(a, 1).value))
        else:
            graph[int(sheet.cell(a, 0).value)] = set([int(sheet.cell(a, 1).value)])
        a = a + 1

def BFS(graph,start):
	visited = []
	queue = [start]
	flag =  0
	print("BREATH FIRST SEARCH")
	while queue:
		node = queue.pop(0)
		if visited.__contains__(node) == False:
			if flag != 0:
				print("->", end = " ")
			else:
				flag = 1
			print(node,end = " ")
			visited.append(node)
			if(graph.keys().__contains__(node)):	
				adjacents = graph[node]
				for adjacent in adjacents:
					queue.append(adjacent)
	print()
	return visited

def DFS(graph, start, visited=None):
	if visited is None:
		visited = set()
		flag = 0
		print("DEPTH FIRST SEARCH")
	else:
		flag = 1
	
	if visited.__contains__(start) == False:
		visited.add(start)
		if flag == 1:
			print("->", end = " ")
		print(start, end = " ")
		if(graph.keys().__contains__(start)):
			for item in graph[start] - visited:
				DFS(graph, item, visited)
	return visited

graph = readXLS()
BFS(graph,1)
DFS(graph,1)