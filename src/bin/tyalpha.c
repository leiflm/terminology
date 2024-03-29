#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <Eina.h>
#include "tycommon.h"

int
main(int argc, char **argv)
{
   int i, perm = 0;

   ON_NOT_RUNNING_IN_TERMINOLOGY_EXIT_1();

   if (argc <= 1)
     {
        printf("Usage: %s [-p] on|off|<opacity level>\n"
               "  Change the terminal transparency on or off\n"
               "  -p  Make change permanent (stored in config)\n"
               "\n",
               argv[0]);
        return 0;
     }
   for (i = 1; i < argc; i++)
     {
        char tbuf[PATH_MAX];

        if (!strcmp(argv[i], "-p"))
          {
             perm = 1;
             i++;
             if (i >= argc) break;
          }
        if (perm)
          snprintf(tbuf, sizeof(tbuf), "%c}ap%s", 0x1b, argv[i]);
        else
          snprintf(tbuf, sizeof(tbuf), "%c}at%s", 0x1b, argv[i]);
        if (write(0, tbuf, strlen(tbuf) + 1) != (signed)(strlen(tbuf) + 1)) perror("write");
     }
   return 0;
}
