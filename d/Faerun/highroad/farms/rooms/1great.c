/*
 * Great room of farmhouse 
 * By Finwe, August 2006
 */
 
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
 
inherit BASE_FARMHOUSE;

void
create_house_room()
{
    set_short("A large great room");
    set_long("This is the great room of the farmhouse. It's large and where the family gathers during the day. Furniture is spread around the room. The walls are decorated with pictures. A large carpet covers the floor, and a dining room sits in one corner of the room. A fireplace is set against a wall and warms the house.\n");

    reset_room();

    add_exit(FROOM_DIR + "1kitchen",  "north");
    add_exit(FROOM_DIR + "1yard",     "south");
    add_exit(FROOM_DIR + "1bedroom",  "east");
    
    set_add_great_room();
    set_add_rug("oval");
    set_add_fireplace();
    set_extra_window("");
    
    num_of_windows = 5;

}


void
reset_room()
{
}
