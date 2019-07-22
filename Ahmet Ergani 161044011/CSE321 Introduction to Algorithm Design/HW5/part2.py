def false_algorithm(n,M,data): #part a
    result = 0
    current_city = 0
    print("*************")
    for i in range(0,n):
        if data[i][current_city] > data[i][(current_city + 1) % 2]:
            current_city = (current_city + 1) % 2
            result += M
        result += data[i][current_city]
    print("result of the false algorithm is ", result)

def algorithm(n,M,data): #part b 
    #starting from NY
    result0 = [] 
    #starting from SF
    result1 = []         

    for index in range(n):
        if index == 0:
            result0.append(data[index][0])
            result1.append(data[index][1])
        else:
            #minimum values of each cities
            NY = min(result0[index-1], result1[index-1] + M) 
            SF = min(result1[index-1], result0[index-1] + M) 
            #appending the minimum values
            result0.append(data[index][0] + NY)
            result1.append(data[index][1] + SF)
    #return the city with the minimum cost        
    return min(result0[n - 1], result1[n - 1])

data = [[1,50],[3,20],[20,2],[30,4]]
print("Total cost of the best path is %d" % (algorithm(4,25,data)))
false_algorithm(4,100,data)
print("the result of the false algorithm hould have been 54 because the cost was too high but the false algorithm never even checked the cost when travelling between cities")

