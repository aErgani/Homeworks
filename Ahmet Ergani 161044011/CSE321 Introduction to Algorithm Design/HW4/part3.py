#modified the typical merge sort for this part
def merger(lists):
    if len(lists) == 0:
        return 
    if len(lists) == 1:
        return lists[0]
    mid = int(len(lists) / 2)
    left = lists[0: mid]
    right = lists[mid: len(lists)]
    leftResult = merger(left)
    rightResult = merger(right)
    return merge(leftResult,rightResult)

def merge(left, right):
    result = []
    i = 0
    j = 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i = i + 1
        else:
            result.append(right[j])
            j = j + 1
    while i < len(left):
        result.append(left[i])
        i = i + 1
    while j < len(right):
        result.append(right[j])
        j = j + 1
    return result

input = []
input.append([1,5,9,13])
input.append([2,6,10,14])
input.append([3,7,11,15])
input.append([4,8,12,16]) 
print(input)    
print(merger(input))