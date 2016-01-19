#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <memory>
#include <boost/shared_ptr.hpp>

using namespace std;

void *_ThreadStart(void *arg);
class Thread {
public:
  Thread(){};
  int Start(){
    Setup();
    int code = pthread_create(&ThreadId_, NULL, _ThreadStart, (void *)this);
    return code;
  }
  int Join(){
    int code = pthread_join(ThreadId_, NULL);
    return code;
  }
  virtual void Setup(){};
  virtual void Execute(){};
private:
  pthread_t ThreadId_;
  void * Arg_;
};
void *_ThreadStart(void *arg){
  ((Thread *)arg)->Execute();
}


///
///
///

bool do_delete = true;


typedef vector<int> Elem;
typedef boost::shared_ptr<Elem> ElemPtr;
typedef boost::shared_ptr<vector<ElemPtr> > ElemPtrVec;

class Mutator : public Thread {
  bool loop;
public:
  Mutator(){}
  void Setup (){
    loop = true;
  }
  void Execute(){
    while (loop) {
      ElemPtrVec v = ElemPtrVec(new vector<ElemPtr>());
      // mutator
      for (int k = 0; k < 2000; k++) {
	v->push_back(ElemPtr(new Elem(1000000)));
      }
      //
#if 0 // usually we need this
      if ( do_delete ) {
	for (vector<ElemPtr>::iterator i = v->begin();
	     i != v->end(); i++){
	       delete (*i);
	     }
	delete v;
      }
#endif
      usleep(0);
      cout << '\b' << "-";
    }
  }
    
  void end() {
    loop = false;
  }
};


class Sort : public Thread {
  struct timeval tv;
  struct timezone tz;
  float time;

  void print_arr(vector<int> a){
    for (int i = 0; i< a.size(); i+=1000) {
      cout << a[i];
    }
    gettimeofday(&tv, &tz);
    float elapsedtime =  tv.tv_sec*1000 + tv.tv_usec/1000.0;
    cout << " " << (elapsedtime-time) << " ms" << endl;;
    time = elapsedtime;
  }

  void scramble(vector<int> *a) {
    double f = 10.0 / (double) a->size();
    for (int i = a->size()-1; --i >= 0;) {
      (*a)[i] = (int)(i * f);
    }
    for (int i = a->size()-1; --i >= 0;) {
      int j = (int)(i * (float)random()/RAND_MAX);
      int t = (*a)[i];
      (*a)[i] = (*a)[j];
      (*a)[j] = t;
    }
  }

  void sort(vector<int> *a) {
    for (int i = a->size()-1; --i>=0; ) {
      bool swapped = false;
      for (int j = 0; j<i; j++) {
	if ((*a)[j] > (*a)[j+1]) {
	  int T = (*a)[j];
	  (*a)[j] = (*a)[j+1];
	  (*a)[j+1] = T;
	  swapped = true;
	}
      }
      if ( i % 10 == 0 ) print_arr(*a);
      if (!swapped)
	return;
    }
  }
  
public:
  vector<int> arr;
  Sort(){}
  void Setup (){
    arr.resize(50000);
  }
  void Execute(){
    cout << "** start Sort *****" << endl;
    scramble(&arr);
    print_arr(arr);
    sort(&arr);
    print_arr(arr);
    cout << "** done Sort ********" << endl;
  }
};

#include <gtest/gtest.h>
// Declare a test
TEST(TestSuite, testCase1)
{
  // dummy test
}

int main(int argc, char *argv[]){
  cout << argc << endl;
  if ( argc > 1) if (!strcmp(argv[1], "--no-delete")) {
    do_delete = false;
    cerr << "NO DELETE mode" << endl;
  }
  Sort *sort = new Sort();
  Mutator *mutator = new Mutator();
  sort->Start();
  mutator->Start();
  sort->Join();
  mutator->end();
  mutator->Join();

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  return 0;
}

