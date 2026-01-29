/* 
 * Outer road of Telberin
 * By Finwe, January 1997
 */

#include "default.h"

inherit AVENUE;


void
create_avenue()
{
    add_my_desc("\n\n");                
    add_exit(AVENUE_DIR + "road01", "south");
    add_exit(AVENUE_DIR + "ave10", "east");
    add_exit(AVENUE_DIR + "ave08", "northwest");
    set_alarm(1.0,0.0,"reset_room");
}

void
reset_room()
{
}
