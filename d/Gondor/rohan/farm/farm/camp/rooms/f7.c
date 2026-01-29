/*
 * Dunlending Camp Outdoor Room
 *
 * --Raymundo, March 2020
 */

#pragma strict_types

inherit "/d/Gondor/rohan/farm/farm/camp/lib/base_room";

#include <macros.h>
#include "/d/Gondor/defs.h"
#include "defs.h"

#define NORTH    "f5"
#define SOUTH    "m5"
#define EAST    "f8"
#define WEST    "m2"
#define SE        "f10"
#define SW        "m4"
#define NW        "f4"
#define NE        "f6"


object guard;

void
create_dunlending()
{
    set_short("In a forest in Anorien");
    set_long("Bordering a rich open meadow, the forest here is thinner "
        + "than it is to the north and east. Rabbits dart to and fro, and "
        + "even the occasional bear rambles through. Herbs poke up through "
        + "the pine needles, evidence of how fertile the soil is.\n");

    add_item("soil", "The soil must be rich and fertile, with all the herbs "
        + "growing around here.\n");

    add_forest_meadow("south and west");

    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast", 0,0,1);
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0,0,1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest", 0,0,1);
    add_exit(CAMP_ROOM_DIR + SE, "southeast");


    add_forest();
    forest_herbs_2();
    if(!random(3))
    {
        forest_climb("f7_up");
    }

    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}

void
add_buck()
{
    add_npc("/d/Gondor/common/npc/buck");
       return ;
}