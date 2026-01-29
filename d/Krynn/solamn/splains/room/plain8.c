/* created by Aridor 06/21/93 */

#include "../local.h"

inherit ROOM + "changeroom";

void
create_change_room()
{
    set_short("On the plains");
    set_long(plains_describe() + "Well, only directly to the east there " +
	     "is a river cutting through the plains, so you cannot go " +
	     "there.\n");

    set_noshow_obvious(1);
    add_exit(ROOM + "river5","southeast",0,3);
    add_exit(ROOM + "plain7","west",0,3);
    add_exit(ROOM + "river4","north",0,3);
    add_exit(ROOM + "plain14","south",0,3);

    set_auto_reset(TABLE);
    reset_room();
}
