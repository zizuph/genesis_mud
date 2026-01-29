/*
 * Orc camp tower
 * By Finwe, December 2007
 */

#include "defs.h"

inherit OC_TOWER_BASE;


void
create_tower_room()
{
    setuid(); 
    seteuid(getuid());

    reset_faerie_room();

    set_short("Fourth level of the tall tower");
    set_long(short() + ". The walls are scratched and look dirty from all the activity up here. Debris is scattered around, cluttering the tower. Holes in the wall provide some light here, and a ladder sits in a corner, allowing travel between the levels.\n");

    add_tower_stuff();

    add_exit(OC_DIR + "underttop", "up");
    add_exit(OC_DIR + "undert02", "down");
}


public void
init()
{
    ::init();

}
void
reset_faerie_room()
{
    create_orcs(ORC_GUARD, NO);
}
