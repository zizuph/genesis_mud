inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

void
create_room()
{
    set_short("In the servant's quarters");
    set_long("You now stand in the servant's quarters. There are "+
    "may little cots in the room, where the servents sleep. Small "+
    "chests hold their meager belongings, and the room is not "+
    "decorated at all.\n");

    add_item("cots","A few servents are sleeping in these little "+
    "cots.\n");
    add_item("chests","They are small chests where servents keep "+
    "their stuff.\n");

    INSIDE;

    add_exit(NOBLE(aemilius/m9),"west",0,-1,-1);
}
