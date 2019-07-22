def f(array):
	low = 0
	high = len(array) - 1
	while low <= high:
		mid = (low + high) // 2
		if array[mid] == mid:
			return mid
		elif array[mid] < mid:
			low = mid + 1
		else:
			high = mid - 1
	return -1

A = [-1,0,1,2,4,6,7]
result = f(A)
if result == -1:
	print("NO SUCH INDEX EXISTS")
else:
	print("THE VALUE AT INDEX",result,"IS ALSO",result)
