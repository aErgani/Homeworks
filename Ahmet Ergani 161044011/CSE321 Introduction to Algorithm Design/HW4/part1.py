def penalty(new_stop,last_stop):        #Calculates the penalty between 2 stops
    A = 200 - (new_stop - last_stop)
    return A ** 2

def longTrip(last_stop,path):
    A = [190,220,410,580,640,770,950,1100,1350] 
    if last_stop == 8:      #means we reached the end
        return
    if last_stop == -1:     #means this is the initial call
        new_stop = 0
        check = penalty(A[new_stop],0)
    else:    
        new_stop = last_stop + 1
        check = penalty(A[new_stop],A[last_stop])
    if check == 0 :         #means the path is perfect
        path.append(new_stop)
        longTrip(new_stop,path)
    else:
        while 1:            #calculates other paths and compares it to previous path's penalty
            print(last_stop," ",new_stop)
            if new_stop == 8:
                break
            if last_stop == -1:
                check2 = penalty(A[new_stop + 1],0)
            else:
                check2 = penalty(A[new_stop + 1],A[last_stop])
            print(check," ",check2)
            if check2 == 0:
                check = check2
                new_stop = new_stop + 1
                break
            if check2 <= check:
                check = check2
                new_stop = new_stop + 1
            elif check2 > check:
                break
        path.append(new_stop)
        longTrip(new_stop,path)
B = []
longTrip(-1,B)
print(B)