/* 
 * Outer road of Telberin
 * By Finwe, January 1997
 */
 
#include "default.h"
 
inherit AVENUE;
 
 
void
create_avenue()
{
    add_my_desc("\n" +
        "A statue has been erected here.\n\n");
 
    add_item( ({"statue"}),
        "A statue of an elven maiden has been placed here. She is " +
        "bending over to pick a flower. The statue has captured " +
        "the ageless beauty of the elves. As such, " +
        "this is one of the Queen's favorite statues.\n");

    add_exit(AVENUE_DIR + "ave32", "north");
    add_exit(THIS_DIR + "rg01",  "east");
    add_exit(AVENUE_DIR + "ave30", "southeast");
    set_alarm(1.0,0.0,"reset_room");
}
 
void
reset_room()
{
}
