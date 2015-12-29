static int (*g)();

int setlfunc(int (*f)()) {
    g = f;
}

int callfunc(x)
{
    return ((*g)(x));
}
