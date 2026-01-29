/* created by Aridor 06/21/93 */

#include "../local.h"

inherit ROOM + "changeroom.c";

void
create_change_room()
{
    set_short("On the plains");
    set_long(plains_describe());

    set_noshow_obvious(1);
    add_exit(ROOM + "plain1","west",0,3);
    add_exit(ROOM + "plain3","east",0,3);
    add_exit(ROOM + "plain19","north",0,3);
    add_exit(ROOM + "plain5","south",0,3);
}



