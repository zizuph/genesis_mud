/* created by Aridor 06/21/93 */

#include "../local.h"

inherit ROOM + "changeroom";

/*actually i'd like a waterhole here!!!*/

void
create_change_room()
{
    set_short("On the plains");
    set_long(plains_describe());

    set_noshow_obvious(1);
    add_exit(ROOM + "plain19","west",0,3);
    add_exit(ROOM + "plain3","south",0,3);
    add_exit(ROOM + "river3","east",0,3);
    add_exit(ROOM + "plain18","north",0,3);
}



