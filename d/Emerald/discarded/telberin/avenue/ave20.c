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
    add_exit(AVENUE_DIR + "ave19", "northeast");
    add_exit(THIS_DIR + "adv_foyer", "north");
    add_exit(AVENUE_DIR + "ave21", "west");
    set_alarm(1.0,0.0,"reset_room");
}
 
void
reset_room()
{
}
