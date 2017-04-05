#include <boost/dynamic_bitset.hpp>


class test
{
    static const int index = 5;
    enum { eIndex = 5 };
    char* a;
public:
    test()
    {
        a = new char[10];
        for (int i = 0; i < 10; i++)
            a[i] = i;
    }
};

int main(int argc, const char* argv[])
{
    test x;
    return 0;
}
