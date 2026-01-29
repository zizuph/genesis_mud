/* created by Aridor 06/21/93 */

#include "../local.h"

inherit ROOM + "changeroom";

void
create_change_room()
{
    set_short("On the plains");
    set_long(plains_describe("north","east"));

    set_noshow_obvious(1);
    add_exit(ROOM + "road1","north",0,3);
    add_exit(ROOM + "road1a","east",0,3);
    add_exit(ROOM + "plain9","south",0,3);
    add_exit(ROOM + "mount4","west",0,3);
}



