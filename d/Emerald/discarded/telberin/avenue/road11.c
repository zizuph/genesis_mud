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
    add_exit(AVENUE_DIR + "road10", "north");
    add_exit(THIS_DIR + "bank",  "south");
    add_exit(AVENUE_DIR + "road12", "southwest");
    set_alarm(1.0,0.0,"reset_room");
}
 
void
reset_room()
{
}
