This was a project for Systems Programming course. It consists of three parts: image editor, image database, and image retrieval.

First part is a simple image editor that supports three different functions.
Red-removal: Takes an input image and removes the red from it.
Black-white: Converting an input image to black and white.
Instagram: The instagram function, which converts an image to a square image.

Second part is a simple image database created using C structs and pointers to build a binary search tree for storing images. The database supports three 
different functions:

The user can add new images to the database by specifying the file name and the values for the three attributes.
The user can query the database by specifying the values for the three attributes and the database will return the names of all image files that match these 
attributes.
The user can ask to have the database contents printed to the screen (i.e. the names of all files stored in the database together with their attributes).

Third part is an image retrieval program that uses fork and pipes to search for similar images. The main program is provided with the name of a ppm image 
file and the name of the directory where we want to look for similar images. The program searches the directory for sub-directories and fork a new process 
for each sub-directory. Each child process compares the original image to all the images in the sub-directory that it was assigned. It then sends to 
the parent process information on the most similar image in its sub-directory.
