/* created by Aridor 06/21/93 */

#include "../local.h"

inherit ROOM + "changeroom";

void
create_change_room()
{
    set_short("On the plains");
    set_long(plains_describe());

    set_noshow_obvious(1);
    add_exit(ROOM + "plain5","west",0,3);
    add_exit(ROOM + "plain7","east",0,3);
    add_exit(ROOM + "plain3","north",0,3);
    add_exit(ROOM + "plain12","south",0,3);

    set_auto_reset(TABLE,random(2)+1);
    reset_room();
}



