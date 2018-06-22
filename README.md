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
  
# What we are doing
## The main target
Reconstructing the road and blocks from the data and generate digitalized graph which could help detecting road, searching path, etc.

## Problems we faced
By adding dots in a single matrix, the density on each road is not uniform. The dots near the cross road are obviously higher and there are much noise which prevents our recognizing-cross road process.
Now we need to find a way to fliter the noise and recognize cross roads (in terms of pixel location) and where are the roads on the image.

# How to perform the demo
1. Make the executable
  Since the data is too big, we save the footprints in a matrix file. But there are still some other operations that requires the data. Thus, you need to put two data file under the /data folder. Please be aware of the file name has to be exactly 'gps_20161101' and 'order_20161101'.

2. Compile the file
  a. linux environment
    Simply move your directory to the /code folder, then simply type:
    '''makefile
    make
    '''
  b. windows environment
    You need to have your visual code installed and be avaliable to compile normal file. By open the project folder using visual code, press 'ctrl+shift+B', the editer should compile it self.

3. Use the demo
  Open the terminal or powershell and move to the /code directory. There should be an exectuable avaliable. Take linux for example, type
  '''
  ./main.out
  '''
  There would be a prompt displayed on the screen that tells basically what the program will do if you type the following thing as the first parameter in the command line.

  By executing the demo, type
  '''
  ./main.out demo
  '''
  The process is displayed on the screen, and then it will shows how many nodes are recognized connected. And you should input which nodes you want the program find connected and the path. Then you can find three file under the /demo folder. And you can see the nodes that are in the path way and those nodes recognized by the program.

# Report Git repo on overleaf
  [DiDi Project report]{https://git.overleaf.com/17224708mvbtnjwqrwzb}