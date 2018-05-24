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
