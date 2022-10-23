#include "prompt.h"
#include "execute.h"

int main()
{
    initialize();

    while (1)
    {
        prompt();
        fflush(stdout);

        size_t n = 100;
        char *input = (char *)malloc(n);
        input = takeinp();

        printf("\n");
        writeHistory(input);

        char *token = strtok(input, ";");
        if (token != NULL)
        {
            allcmds[0] = token;
        }
        int k = 1;
        while (token != NULL)
        {
            token = strtok(NULL, ";");
            if (token != NULL)
            {
                allcmds[k] = token;
                k++;
            }
        }

        for (int i = 0; i < k; i++)
        {
            execute(allcmds[i]);
        }
    }
}