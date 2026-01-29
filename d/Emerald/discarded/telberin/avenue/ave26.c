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
    add_exit(AVENUE_DIR + "road09",  "north");
    add_exit(AVENUE_DIR + "ave25",   "south");
    add_exit(THIS_DIR + "gen_ofc", "east", "@@closed");
    add_exit(AVENUE_DIR + "ave27",   "northwest");
    set_alarm(1.0,0.0,"reset_room");
}
 
int
closed()

{
    write("The Genealogy office is closed due to a recent fire that "+
        "destroyed nearly all the records held here.\n");
    return 1;
}
void
reset_room()
{
}
