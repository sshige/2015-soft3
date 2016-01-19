/*---------------------------------------------
 *
 * A Tree Search kit for experimenting with graph
 * formulated or network problems such as the 
 * Romanian road network problem as described in 
 * Russell and Norvig, Chapter 3.
 *
 * Last Modified:  28.7.04, KAH
 *
 * $Id: graphsearch.cpp,v 1.1 2010-01-22 03:35:47 k-okada Exp $
 *---------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <assert.h>
#include <unistd.h>
#include <algorithm>
#include <list>
#include <string.h>

using namespace std;
class Node {
public:

  int state;
  // previous or parent node instance in the search tree
  Node *parentptr;
  // not yet used - could be used as child index
  int action;
  //depth in the tree  root is 1
  int depth;
  // same as  depth at present
  int pathCost;
  // normal constructor
  Node(int s, Node * p) {
    state = s;
    parentptr = p;
    if (parentptr == NULL) {
      depth = 1;
    } else {
      depth = parentptr->depth + 1;
    }
  }
  ~Node() {
  }				// destructor
  Node(const Node & node) {	// copy constructor
    state = node.state;
    parentptr = node.parentptr;
    depth = node.depth;
  }
  Node * parent() {
    // return a pointer to this instance's parent instance
    if (parentptr != NULL)
      return parentptr;
	
    else
      return this;
  }
  // count of all instances created by factory
  static int count;		
  // all factory-created instances
  static vector < Node * >all;
  static Node *factory() {
    return factory(-1, NULL);
  }
  static Node *factory(int s) {
    return factory(s, NULL);
  }
  static Node *factory(int s, Node * p) {
    Node * retval = new Node(s, p);
    all.push_back(retval);
    count++;
    return retval;
  }
  
  // free up memory  from all factory-created instances
  static void freeall() {
    for (int i = 0; i < all.size(); i++)
      delete all[i];
    all.clear();
  }

  bool operator==(const Node & n) {
    return (state == n.state);
  }
  bool operator!=(const Node & n) {
    return (state == n.state);
  }
};
int Node::count = 0;
// internal list of all factory-created instances
vector < Node * >Node::all;

/*------------------------------------------------*/ 
// Suitable for a graph like proble such as 
// the Romanian road network problem such as
// in Russell and Norvig, 2nd Edition, Chapter 3.
class Problem {
  // map of string-names to integer indices  i=map[string]
 public:map < string, int >indices;
 // names of the vertices (cities)        string=names[i]
 vector < string > names;
 // k=successors[i][j] is jth successor of ith vertex
 vector < vector < int > > successors;
 // w=weights[i][j] is jth weight of arc to ith vertex
 vector < vector < int > > weights;

 // number of vertices (cities) in the graph (roadnetwork)
 int n() {
   return names.size();
 }
 int nSuccessors(int i) {
   return successors[i].size();
 }			// out-degree of ith vertex
 Problem() {
 }			// constructor
 ~Problem() {
 }			// destructor
 void addSuccessor(string src, string dst, int w) {
   successors[indices[src]].push_back(indices[dst]);
   weights[indices[src]].push_back(w);
 }

  void addSuccessorPair(string a, string b, int w) {
   addSuccessor(a, b, w);
   addSuccessor(b, a, w);
 }
 
 void readFile(string filename) {
   // currently wired with test data
	
   // first pass to get city names only:
   ifstream in(filename.c_str());
   assert(in);
   names.clear();
   char line[1024];
   while (in.getline(line, sizeof(line), '\n')) {
     // ignore  comment lines in the file
     if (line[0] != '#') {
       // whitespace possible delimiters
       char *delimiters = " \t\n";
       int wordcount = 0;
       char *wordptr;
       // tokenize string
       wordptr = strtok(line, delimiters);
       string source(wordptr);
       addName(source);	// add if it exists
       while ((wordptr = strtok(NULL, delimiters))
       != NULL) {
	 wordcount++;
	 string destination(wordptr);
	 addName(destination);	// add if it exists
       }
     }
   }
   in.close();
   for (int i = 0; i < names.size(); i++) {
     indices[names[i]] = i;
   } vector < int >dummy;	// an empty vector<int> 
   // sets up 1st dimension  with n() copies of dummy
   successors.assign(n(), dummy);
   // sets up 1st dimension  with n() copies of dummy
   weights.assign(n(), dummy);
	
   // second pass to get arcs:
   ifstream in2(filename.c_str());
   assert(in2);
   while (in2.getline(line, sizeof(line), '\n')) {
     // ignore  comment lines in the file
     if (line[0] != '#') {	
       // whitespace possible delimiters
       char *delimiters = " \t\n";
       int wordcount = 0;
       char *wordptr;
       // tokenize string
       wordptr = strtok(line, delimiters);
       string source(wordptr);
       // should already exist
       assert(nameExists(source));
       while ((wordptr = strtok(NULL, delimiters)) != NULL) {
	 wordcount++;
	 string destination(wordptr);
	 // should already exist
	 assert(nameExists(destination));
	 addSuccessor(source, destination, 1);
       }
     }
   }
   in2.close();
 }
 bool nameExists(string name) {	
   // does a name alredy exist in vocabulary of names?
   for (vector < string >::iterator it = names.begin();
	it != names.end(); it++) {
     if (name == *it)
       return true;
   }
   return false;
 }
 void addName(string name) {	// add name to names only if it is
   // not already in vocabulary
   if (!nameExists(name)) {
     names.push_back(name);
   }
 }
 void testProblem() {
   addName(string("Arad")); // get all the city names on first pass
   addName(string("Zerend"));
   addName(string("Oradea"));
   addName(string("Sibiu"));
   addName(string("Fagaras"));
   addName(string("Bucharest"));
   for (int i = 0; i < names.size(); i++) {
     indices[names[i]] = i;
   }
   vector < int >dummy;	// an empty vector<int> 
   
// sets up 1st dimension  with n() copies of dummy
   successors.assign(n(), dummy);
   // sets up 1st dimension  with n() copies of dummy
   weights.assign(n(), dummy);

   // uniform  (unity)  for the weights
   addSuccessor(string("Arad"), string("Zerend"), 1);
   addSuccessor(string("Arad"), string("Sibiu"), 1);
   addSuccessor(string("Zerend"), string("Arad"), 1);
   addSuccessor(string("Zerend"), string("Oradea"), 1);
   addSuccessor(string("Oradea"), string("Zerend"), 1);
   addSuccessor(string("Oradea"), string("Sibiu"), 1);
   addSuccessor(string("Sibiu"), string("Arad"), 1);
   addSuccessor(string("Sibiu"), string("Oradea"), 1);
   addSuccessor(string("Sibiu"), string("Fagaras"), 1);
   addSuccessor(string("Fagaras"), string("Sibiu"), 1);
   addSuccessor(string("Fagaras"), string("Bucharest"), 1);
   addSuccessor(string("Bucharest"), string("Fagaras"), 1);
 } 
 // printout problem graph for check purposes - writes out each
 // vertex, its out-degree, and its list of successor vertices.
 void print() {
   int bmax = 0;
   for (int i = 0; i < n(); i++) {
     cout << names[i] << " (" << nSuccessors(i) << "):: ";
     bmax = bmax > nSuccessors(i) ? bmax : nSuccessors(i);
     for (int j = 0; j < nSuccessors(i); j++) {
       cout << names[successors[i][j]] << ",";
     } cout << endl;
   } cout << "Max breadth b " << bmax << endl;
 }
};


/*------------------------------------------------*/
class Queue:public deque < Node * > {
public:virtual Node * First() {
};
  virtual void Insert(Node * n) {
  };
  virtual Node * RemoveFirst() {
  };
};

class FIFOQueue:public Queue {
				// a FIFO Queue
public:Node * First() {
  return back();
}
  void Insert(Node * n) {
    return push_front(n);
  }
  Node * RemoveFirst() {
    Node * r = First();
    pop_back();
    return r;
  }
};

class LIFOQueue:public Queue {
				// a LIFO Queue
public:Node * First() {
  return front();
}
  void Insert(Node * n) {
    return push_front(n);
  }
  Node * RemoveFirst() {
    Node * r = First();
    pop_front();
    return r;
  }
};


/*------------------------------------------------*/
int main(int argc, char *argv[])
{
  int c;
  char *fname = NULL;
  enum { BFS, DFS, DLS, IDS } search_algorithm = BFS;
  bool recursive_check = false;
  int depth_limit = 1;
  while ((c = getopt(argc, argv, "f:bdl:igr")) != -1) {
    switch (c) {
    case 'f':
      fname = optarg;
      break;
    case 'b':
      search_algorithm = BFS;
      break;
    case 'd':
      search_algorithm = DFS;
      break;
    case 'l':
      search_algorithm = DLS;
      depth_limit = atoi(optarg);
      break;
    case 'i':
      search_algorithm = IDS;
      break;
    case 'r':
      recursive_check = true;
      break;
    default:
      cerr << "Unknown option " << c << endl;
      exit(1);
    }
  }
  cout << ";; Selecting ";
  switch (search_algorithm) {
  case BFS:
    cout << "Breadth-first Search";
    break;
  case DFS:
    cout << "Depth-first Searach";
    break;
  case DLS:
    cout << "Depth-limited Search " << depth_limit;
    break;
  case IDS:
    cout << "Iterative Deppting Search";
    break;
  }
  cout << endl << endl;;
  Problem problem;
  if (fname) {
    problem.readFile(string(fname));
  } else {
    problem.testProblem();
  }
  problem.print();
  cout << endl;
  string goalName("Bucharest");
  string startName("Arad");
  Queue * fringe;
  switch (search_algorithm) {
  case BFS:
    fringe = new FIFOQueue();
    break;
  case DFS:
  case DLS:
  case IDS:
    fringe = new LIFOQueue();
    break;
  }
  vector < Node > closed;
 IDS_RESTART:
  Node * nodeptr =
    (Node::factory(problem.indices[startName]));
  fringe->Insert(nodeptr);
  bool success = false;
  while (!success) {
    if (fringe->empty())
      break;		// IF-EMPTY -> FAILURE
    nodeptr = fringe->RemoveFirst();	// REMOVE-FIRST
    cout << "considering " << 
      problem.names[nodeptr->state] << endl;
	
    // GOAL-TEST
    int i = nodeptr->state;
    if (problem.names[i] == goalName) {
      success = true;
      break;
    }
	
    // DEPTH-TEST
    if ((search_algorithm == DLS ||
	 search_algorithm == IDS) 
	&&nodeptr->depth >= depth_limit) {
      success = false;
      break;
    }
	
    // state is not in cloased
    if (recursive_check == false
	|| find(closed.begin(), closed.end(),
		*nodeptr) == closed.end()) {
    closed.push_back(*nodeptr);
    for (int j = 0; j < problem.nSuccessors(i); j++) {	// EXPAND
      Node *nextnode =
	Node::factory(problem.successors[i][j],
		      nodeptr);
      // diagnostics
      cout << "    " 
	   << problem.names[problem.successors[i][j]]
	   << " from "
	   << problem.names[i]  <<endl;
      fringe->Insert(nextnode);
    } 
    }
  } if (search_algorithm == IDS && !success) {
    closed.clear();
    depth_limit++;
    cerr << ">> Deeping ... " << depth_limit << endl;
    goto IDS_RESTART;
  }
    
  // report on the solution path found by back tracing parent pointers
  if (!success) {
    cout << "Failure!" << endl;
  } else {
    cout << endl << "Solution: " << endl;
    while (problem.names[nodeptr->state] != startName) {
      cout << problem.names[nodeptr->
			   state] << "(depth " << nodeptr->
	depth << ")" << endl;
      nodeptr = (nodeptr->parent());
    }
    cout << startName << "(depth " << nodeptr->depth << ")" << endl;
  }
  Node::freeall();		// free up space
  cout << endl << Node::all.size() << " Nodes left" << endl;
  cout << endl << Node::count << " Nodes created" << endl;
}


/*------------------------------------------------
  Development Notes:
 
  The C++ STL queue with pop and front implements
   a FIFO queue.  This gives a BFS tree search.

  The C++ Stack is a LIFO  - use  top and pop.

  Both implement  push  which  pushes  onto end of the Queue.

  @KAH 2004--------------------------------------*/ 
    
