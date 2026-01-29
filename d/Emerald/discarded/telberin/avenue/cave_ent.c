/* 
 * The cave entrance to the fire drake caverns in Telberin
 * By Finwe, January 1997
 */
 
#include "default.h"
 
inherit AVENUE;
 
 
void
create_avenue()
{
    add_my_desc("\n\n");                
 
    add_exit(AVENUE_DIR + "ave13",  "north");
    add_exit(AVENUE_DIR + "ave14", "south");
    set_alarm(1.0,0.0,"reset_room");
}
