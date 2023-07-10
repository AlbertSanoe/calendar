#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

#include "include/macro.h"
#include "include/terminal.h"

#define LOCAL_DEBUG 1
#if (GLOBAL_DEBUG == 1) && (LOCAL_DEBUG == 1)

#define TRY_DEBUG

#endif

int main(int argc, char *argv[])
{
#ifdef TRY_DEBUG
    DEBUG("%d\n", argc);
#endif
    if (argc != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("%s\n", argv[1]);
#endif
        if (strcmp(argv[1], "xcal") == 0 && argc != 2)
        {
            std::vector<std::string> stringVec;
            for (int i = 2; i < argc; i++)
            {
                stringVec.push_back(std::string(argv[i]));
            }
            xcal_process(argc-2,stringVec);
        }
        else if (strcmp(argv[1], "xcc") == 0)
        {
        }
        else
        {
            printf("Please enter valid command-line arguments\n");
        }
    }
    else
    {
        printf("Please enter valid command-line arguments\n");
    }

    return 0;
}
