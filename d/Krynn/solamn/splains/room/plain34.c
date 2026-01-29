/* created by Aridor 06/21/93 */

#include "../local.h"

inherit ROOM + "changeroom";

void
create_change_room()
{
    set_short("On the plains");
    set_long(plains_describe());

    set_noshow_obvious(1);
    add_exit(ROOM + "river17","west",0,3);
    add_exit(ROOM + "plain35","east",0,3);
    add_exit(ROOM + "plain29","north",0,3);
    add_exit(ROOM + "river15","south",0,3);

    set_auto_reset(TABLE);
    reset_room();
}



