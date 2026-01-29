/* created by Aridor 06/21/93 */

#include "../local.h"

inherit ROOM + "changeroom";


void
create_change_room()
{
    set_short("On the plains");
    set_long(plains_describe() + "Well, only directly to the west there " +
	     "is a river cutting through the plains, so you cannot go " +
	     "there.\n");

    set_noshow_obvious(1);

    add_item("river","The river comes from the west and flows to towards " +
	     "the south from here.\n");
    add_exit(ROOM + "river18","northwest",0,3);
    add_exit(ROOM + "river17","south",0,3);
    add_exit(ROOM + "plain15","north",0,3);
    add_exit(ROOM + "plain29","east",0,3);

    set_auto_reset(TABLE);
}
