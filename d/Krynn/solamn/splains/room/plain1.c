/* created by Aridor 06/21/93 */

#include "../local.h"

inherit ROOM + "changeroom";

void
create_change_room()
{
    set_short("On the plains");
    set_long(plains_describe("south","west"));

    set_noshow_obvious(1);
    add_exit(ROOM + "road1","west",0,3);
    add_exit(ROOM + "road1a","south",0,3);
    add_exit(ROOM + "plain2","east",0,3);
    add_exit(ROOM + "mount1","north",0,3);
}



