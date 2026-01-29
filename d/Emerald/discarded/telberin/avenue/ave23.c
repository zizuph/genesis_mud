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
    add_exit(THIS_DIR + "t1",    "northeast");
    add_exit(THIS_DIR + "cloak_shop", "west");
    add_exit(AVENUE_DIR + "ave24", "northwest");
    add_exit(AVENUE_DIR + "ave22", "south");
    set_alarm(1.0,0.0,"reset_room");
}
 
void
reset_room()
{
}
