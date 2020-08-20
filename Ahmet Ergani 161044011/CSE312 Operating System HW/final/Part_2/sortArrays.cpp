#include "sortArrays.h"

using namespace std;

int main(int argc, char const *argv[])
{
    if(argc < 7)
    {
    	fprintf(stderr, "Insufficient command line parameters. 7 parameters required\n");
    }

    SortArrays sortArrays(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), argv[4], argv[5], atoi(argv[6]), argv[7]);

    return 0;
}

