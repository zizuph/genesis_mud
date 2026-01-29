/*
 * Special routines to get info about objects.
 */


#include "/secure/std.h"


int
FindCallOut(object ob, string fun)
{
    mixed *data;
    int i;

    data = SECURITY->do_debug("call_out_info");

    for(i=0;i<sizeof(data);i++)
	if(data[i] && data[i][0]==ob && data[i][1]==fun)
	    return data[i][2];

    return -1;
}

mixed *
GetCallOutData(object ob, string fun)
{
    mixed *data;
    int i;

    data = SECURITY->do_debug("call_out_info");

    for(i=0;i<sizeof(data);i++)
	if(data[i][0]==ob && data[i][1]==fun)
	    return ({ data[i][2], data[i][3] });
    return ({ -1 });
}
