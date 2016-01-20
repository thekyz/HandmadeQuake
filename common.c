#include <stdio.h>
#include "quakedef.h"

int32 com_argc = 1;
char *com_argv[MAX_NUM_ARGVS + 1];

void COM_HandleCmdLine(int32 argc, char **argv)
{
    com_argc = argc + 1;
    for (int32 i = 1; i < argc; i++)
    {
        com_argv[i] = argv[i];
    }
}

void COM_ParseCmdLine(char *lpCmdLine)
{
    com_argv[0] = "";

    while (*lpCmdLine && (com_argc < MAX_NUM_ARGVS + 1))
    {
        while (*lpCmdLine && ((*lpCmdLine <= 32) || (*lpCmdLine > 126)))
            lpCmdLine++;

        if (*lpCmdLine)
        {
            com_argv[com_argc] = lpCmdLine;
            com_argc++;

            while (*lpCmdLine && ((*lpCmdLine > 32) && (*lpCmdLine <= 126)))
                lpCmdLine++;

            if (*lpCmdLine)
            {
                *lpCmdLine = 0;
                lpCmdLine++;
            }
        }
    }

}

int32 COM_CheckParm(char *parm)
{
    for (int32 i = 1; i < com_argc; i++)
    {
        if (!Q_strcmp(parm, com_argv[i]))
            return i;
    }

    return 0;
}
