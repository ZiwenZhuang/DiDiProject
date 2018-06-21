import math

def same(a,b):
    dis=abs(a[0]-b[0])+abs(a[1]-b[1])
    
    if dis<=d:
        return True
    else:
        return False

'''def union(i,j):
    disjoint[i]=j'''
def find_root(i,set_num,a_set,visit):
    #change=[]
    visit[i]=1
    if disjoint[i] != i:
        a_set.append([])
        while disjoint[i] != i:
            a_set[set_num[0]].append(i)
            #change.append(i)
            i=disjoint[i]
            visit[i]=1
        a_set[set_num[0]].append(i)
        #for j in range(len(change)):
        #    disjoint[j]=i
        set_num[0]+=1

        
f = open("corner.bin")             
line = f.readline()
d=20
node_l=[]
visit=[]
while line:
    node=eval(line)
    node_l.append(node)
    line=f.readline()

node_num=len(node_l)
disjoint=[]
for i in range(node_num):
    disjoint.append(i)
    visit.append(0)
for i in range(node_num):
    for j in range(i+1,node_num):
        if same(node_l[i],node_l[j]):
            disjoint[i]=j#union(i,j)
            break

a_set=[]
set_num=[0]
for i in range(node_num):
    if visit[i]==0:
        find_root(i,set_num,a_set,visit)

final_node=[]
for i in range(set_num[0]):
    x=0
    y=0
    for j in a_set[i]:
        x+=node_l[j][0]
        y+=node_l[j][1]
    x=x//len(a_set[i])
    y=y//len(a_set[i])
    final_node.append([x,y])

for i in range(len(final_node)):
    print(final_node[i])
#'''
