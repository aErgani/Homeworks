class Job: 
    time = 0
    weight = 0
    value = 0
    def __init__(self,time,weight):
        self.time = time
        self.weight = weight
    def __str__(self):
        return "%d %d" % (self.time,self.weight)
    def __repr__(self):
        return "%d %d" % (self.time,self.weight)
    def calculate(self):
        self.value = self.weight / self.time

def bubbleSort(Jobs):
    print("sorting by Weight/time")
    for passnum in range(len(Jobs)-1,0,-1):
        for i in range(passnum):
            if Jobs[i].value < Jobs[i+1].value:
                temp = Jobs[i]
                Jobs[i] = Jobs[i+1]
                Jobs[i+1] = temp

def main(Jobs):
    for job in Jobs:
        job.calculate()
    print("[time weight]")
    print(Jobs)
    bubbleSort(Jobs)
    print(Jobs)
    result = 0
    time = 0
    for job in Jobs:
        result += (time + job.time) * job.weight
        print(result)
        time += job.time
    print("***********")
Jobs = []
Jobs.append(Job(4,8))
Jobs.append(Job(2,1))
Jobs.append(Job(6,3))
Jobs.append(Job(1,15))
Jobs.append(Job(7,7))
Jobs.append(Job(14,3))
main(Jobs)