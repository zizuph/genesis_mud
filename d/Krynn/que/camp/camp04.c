#include "local.h"
inherit CAMP_BASE

void
create_camp_room()
{
    set_short("In a camp");
    set_long("This is the western outpost of an army camp, the major part of " +
	     "the camp lies to the east. There is wilderness in all other " +
	     "directions.\n");

    add_exit("camp08","east","@@block@@");
    add_exit(TDIR+"rooms/plain-7-3-v",  "west",  0, 2, 1);
    add_exit(TDIR+"rooms/plain-8-4-v",  "south", 0, 2, 1);
    add_exit(TDIR+"rooms/plain-8-2-v",  "north", 0, 2, 1);

    set_auto_reset("tblwarkiri",random(4)+2);
    reset();
}
