def CrossingMaxSum(array, left, mid, right) : 
    sum = 0; left_sum = -1
    for i in range(mid, left-1, -1) : 
        sum = sum + array[i] 
        if (sum > left_sum) : 
            left_sum = sum 

    sum = 0; right_sum = -1
    for i in range(mid + 1, right + 1) : 
        sum = sum + array[i] 
        if (sum > right_sum) : 
            right_sum = sum 
    return left_sum + right_sum

def subArrayMaxSum(array, left, right) : 
    if (left == right) : 
        return array[left] 
    mid = (left + right) // 2
    return max(subArrayMaxSum(array, left, mid), subArrayMaxSum(array, mid+1, right), CrossingMaxSum(array, left, mid, right))

array = [5,3,8,-13,-6,7,-1,30] 
n = len(array)
max_sum = subArrayMaxSum(array, 0, n-1) 
print("Max sum is", max_sum) 