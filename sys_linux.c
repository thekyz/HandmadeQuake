#include "linquake.h"
#include "quakedef.h"
#include "stdio.h"


int32 main(int argc, char **argv)
{
    COM_HandleCmdLine(argc, argv);

    int32 test = COM_CheckParm("-setalpha");
    int32 value = Q_atoi(com_argv[test+1]);
    
    printf("value = %d\n", value);
    return 0;
}