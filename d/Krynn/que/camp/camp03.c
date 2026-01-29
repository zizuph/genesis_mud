#include "local.h"
inherit CAMP_BASE

void
create_camp_room()
{
    set_short("In a camp");
    set_long("This is the southern outpost of an army camp, the major part of " +
	     "the camp lies to the north. There is wilderness in all other " +
	     "directions.\n");
        
    
    add_exit("camp12","north","@@block@@");
    add_exit(TDIR+"rooms/plain-8-4-v",  "west",  0, 2, 1);
    add_exit(TDIR+"rooms/plain-9-5-1",  "south", 0, 1);
    add_exit(TDIR+"rooms/plain-10-4-v", "east",  0, 2, 1);

    set_auto_reset("tblwarkiri",random(4)+2);
    reset();
}

