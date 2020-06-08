# Breadth First Search Program

- The program prints out the adjacency list representation of a Graph and finds the shortest paths between 
pairs of vertices of the Graph along with each path's distance.

- Run "make" in a terminal to create "FindPath".

- To use the program in a terminal, run the command: ./FindPath (input file) (output file)

## Input
- The input file will be in two parts. The first part will begin with a line consisting of a single integer n 
giving the number of vertices in the graph. Each subsequent line will represent an edge by a pair of distinct 
numbers in the range 1 to n, separated by a space. These numbers are the end vertices of the corresponding edge. 
The first part of the input file defines the graph, and will be terminated by a dummy line containing “0 0”. 
For instance, the lines below define a graph:

  6  
  1 2  
  1 3  
  2 4  
  2 5   
  2 6  
  3 4   
  4 5  
  5 6  
  0 0  

- The second part of the input file will consist of a number of lines, each consisting of a pair of integers in the 
range 1 to n, separated by a space. Each line specifies a pair of vertices in the graph; a starting point (or source) 
and a destination. The second part of the input file defines the paths the program needs to find and will also be 
terminated by the dummy line “0 0”. The lines below are an example of an entire input file:

  6   
  1 2  
  1 3   
  2 4  
  2 5   
  2 6  
  3 4   
  4 5  
  5 6  
  0 0  
  1 5  
  3 6  
  2 3  
  4 4  
  0 0

## Output

- The input file will have the corresponding output file below:

  1: 2 3  
  2: 1 4 5 6  
  3: 1 4  
  4: 2 3 5  
  5: 2 4 6  
  6: 2 5  

  The distance from 1 to 5 is 2  
  A shortest 1-5 path is: 1 2 5  

  The distance from 3 to 6 is 3  
  A shortest 3-6 path is: 3 1 2 6  

  The distance from 2 to 3 is 2  
  A shortest 2-3 path is: 2 1 3  

  The distance from 4 to 4 is 0  
  A shortest 4-4 path is: 4  

- Check out the files input1.txt, output1.txt, input2.txt, and output2.txt for a better understanding regarding the format!

