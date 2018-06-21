import cv2
import numpy as np
import math
import sys

class NumberOfArgumentsError(LookupError):
    '''raise this when there's a lookup error for my app'''
def CvCorner(filename):
	img = cv2.imread(filename)
	gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
	corners=[]
	# gray=cv2.imread(filename)
	gray = np.float32(gray)
	dst = cv2.cornerHarris(gray,2,7,0.04)

	#result is dilated for marking the corners, not important
	#dst = cv2.dilate(dst,None)

	# Threshold for an optimal value, it may vary depending on the image.
	#img[dst>0.08*dst.max()]=[0,0,255]
	for i in range(np.shape(dst)[0]):
		for j in range(np.shape(dst)[1]):
			if dst[i][j]>0.08*dst.max():
				corners.append([i,j])
	return corners
#cv2.imshow('dst',img)
#if cv2.waitKey(0) & 0xff == 27:
#    cv2.destroyAllWindows()






def cluster(corners,outfile):      
	# f = open("corner.bin")             
	# line = f.readline()
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
	d=20
	node_l=corners
	visit=[]
	node_num=len(node_l)
	disjoint=[]
	out=open(outfile,"w+")
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
		out.write(str(final_node[i])+"\n")
	out.close()
def main():
	print sys.argv
	if len(sys.argv)!=3:
		raise NumberOfArgumentsError("Please enter input file and output file")
	input_file=sys.argv[1]
	output_file=sys.argv[2]
	corners=CvCorner(input_file)
	cluster(corners,output_file)
if __name__ == "__main__":
    main()