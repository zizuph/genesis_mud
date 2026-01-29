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
    add_exit(AVENUE_DIR + "ave07", "east");
    add_exit(AVENUE_DIR + "ave05", "west");
    set_alarm(1.0,0.0,"reset_room");
}
 
void
reset_room()
{
}
