/* 
 * Inner road of Telberin
 * By Finwe, January 1997
 * for sake of clarity, the file names are roadxx
 */
 
#include "default.h"
 
inherit INNER_AVE;
 
 
void
create_avenue()
{
    add_my_desc("\n\n");                
    add_exit(AVENUE_DIR + "road04", "east");
    add_exit(THIS_DIR + "rg03", "west");
    set_alarm(1.0,0.0,"reset_room");
}
 
void
reset_room()
{
}
