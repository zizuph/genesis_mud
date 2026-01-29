/* created by Aridor 06/21/93 */

#include "../local.h"

inherit ROOM + "changeroom";

void
create_change_room()
{
    set_short("On the plains");
    set_long(plains_describe());

    set_noshow_obvious(1);
    add_exit(ROOM + "plain4","north",0,3);
    add_exit(ROOM + "plain23","west",0,3);
    add_exit(ROOM + "plain15","south",0,3);
    add_exit(ROOM + "plain10","east",0,3);
}



