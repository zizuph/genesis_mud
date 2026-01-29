#include "local.h"
inherit CAMP_BASE

void
create_camp_room()
{
    set_short("In a camp");
    set_long("This is the eastern outpost of an army camp, the major part of " +
	     "the camp lies to the west. There is wilderness in all other " +
	     "directions.\n");

    add_exit("camp10","west","@@block@@");
    add_exit(TDIR+"rooms/plain-11-3-p", "east",      0, 2, 1);
    add_exit(TDIR+"rooms/plain-10-4-v", "south",     0, 2, 1);
    add_exit(TDIR+"rooms/plain-10-2-p", "north",     0, 2, 1);
    add_exit(TDIR+"rooms/plain-11-4-1", "southeast", 0, 1);

    set_auto_reset("tblwarkiri",random(4)+2);
    reset();
}
