# DiDiProject
This repository will takes only codes and several configuration file, and no actual data will be pushed

After you clone the repo, please add the data file to the /data folder.

# What should be done as preparation interface:
1. The data object
  Setup a class that read from the file and stores all information of one piece of data. Initially, I want to let it read the file when constructing.
  Also, there could be get/set method for each attribute.

2. The path object
  It is designed to standarlize the paths in the gps file, which simplifies all the gps information into a graph. (Maybe represented in a adjacent list)

3. The order object
  It is used to store the order, start point, end point, path and the time stamps.
  
# What we are doing for now
## The main target
Reconstructing the road and blocks from the data and generate digitalized graph which could help detecting road, searching path, etc.

## Problems we are facing now
By adding dots in a single matrix, the density on each road is not uniform. The dots near the cross road are obviously higher and there are much noise which prevents our recognizing-cross road process.
Now we need to find a way to fliter the noise and recognize cross roads (in terms of pixel location) and where are the roads on the image.
