#include "local.h"
inherit CAMP_BASE

void
create_camp_room()
{
    set_short("In a camp");
    set_long("This is the northern outpost of an army camp, the major part of " +
	     "the camp lies to the south. There is wilderness in all other " +
	     "directions.\n");

    add_exit("camp06","south","@@block@@");
    add_exit(TDIR+"rooms/plain-8-2-v",  "west",  0, 2, 1);
    add_exit(TDIR+"rooms/plain-10-2-p", "east",  0, 2, 1);
    add_exit(TDIR+"rooms/plain-9-1-p",  "north", 0, 2, 1);

    set_auto_reset("tblwarkiri",random(4)+2);
    reset();
}
