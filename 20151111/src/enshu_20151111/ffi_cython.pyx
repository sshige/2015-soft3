cdef extern int hello( char *)
cdef extern double sinc(double)

def hello2(name):
    bname = name.encode("utf-8")
    cdef char * cname = bname
    hello(cname)


def sinc2(x):
    return sinc(x)
