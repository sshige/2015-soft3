all: ffi-c libffiJava.so ffi-c.so callc.so

ffi-c++.o: ffi-c++.cpp
	gcc -c ffi-c++.cpp

ffi-c++-main.o: ffi-c++-main.c
	gcc -c ffi-c++-main.c

ffi-c: ffi-c++.o ffi-c++-main.o
	gcc -o ffi-c $^ -lm

ffiJava.class:
	javac ffiJava.java

ffiJava.h: ffiJava.class
	javah -jni ffiJava

JAVA_HOME=/usr/lib/jvm/java-6-openjdk-amd64/
libffiJava.so: ffiJava.h
	gcc -shared -fPIC -I${JAVA_HOME}/include -o libffiJava.so ffiJava.c
	LD_LIBRARY_PATH=./:${LD_LIBRARY_PATH} java ffiJava

ffi-c.so: ffi-c.c
	gcc -shared -fPIC -o ffi-c.so ffi-c.c -lm
	python ffi_python.py
	eusgl ffi.l

callc.so: callc.c
	gcc -fPIC -shared -o callc.so callc.c
	eusgl callc.l

_ffi_c.so:
	swig -python ffi-c.i
	gcc -I/usr/include/python2.7 -shared -fPIC -o _ffi_c.so ffi-c.c ffi-c_wrap.c
	python -c 'import ffi_c; ffi_c.hello("hello"); print ffi_c.sinc(1.0)'

ffi_c.java:
	swig -java ffi-c.i
	gcc -shared -fPIC -I${JAVA_HOME}/include -o libffi-c_wrap.so ffi-c_wrap.c ffi-c.c
	javac ffi_c.java
	javac ffi_main.java
	LD_LIBRARY_PATH=./:${LD_LIBRARY_PATH} java ffi_main

libffi-class_wrap.so:
	swig -c++ -java ffi-class.i
	g++ -shared -fPIC -I ./ -I${JAVA_HOME}/include -o libffi-class_wrap.so ffi-class_wrap.cxx ffi-class.cpp -lm -lstdc++
	javac ffi_class.java ffi_classJNI.java
	javac ExampleMain.java
	LD_LIBRARY_PATH=./:${LD_LIBRARY_PATH} java  ExampleMain

libffi-c.so:
	gcc -shared -fPIC -o libffi-c.so ffi-c.c -lm
	javac -classpath .:/usr/share/java/jna-3.2.7.jar ExampleMain2.java
	LD_LIBRARY_PATH=./:${LD_LIBRARY_PATH} java -classpath .:/usr/share/java/jna-3.2.7.jar ExampleMain2

ffi_cython.so:
	python setup.py build_ext --inplace
	python -c 'import ffi_cython; ffi_cython.hello2("world"); ffi_cython.sinc2(1.0)'

.PHONY: callc.c

clean:
	rm *.so *.o *.class ffi_c.java ffiJava.h ffi-c_wrap.c ffi_c.java ffi_cJNI.java ffi_class.java ffi_classJNI.java Example.java libffi-c.so ffi_cython.so ffi-c ffi-class_wrap.cxx ffi_c.py ffi_c.pyc ffi_cython.c
