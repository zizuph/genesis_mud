/* Mountain trail room, credit to Sarr */
#pragma strict_types
#include "defs.h"
inherit MTRAIL_ROOM;

void
create_room()
{
    type = "west";
    roadWest = "southwest";
    roadEast = "east";
    ::create_room();
    set_long("You stand at a fork in the trail. It is relativly " +
    "flat here. Looking to the north, you see the trail heads further " + 
    "up the mountain, and you think you see what appears to be a " +
    "castle at the top. To the " + roadEast +
    ", the trail stays flat for a bit, but then turns out of view. " +
    "To the " + roadWest + " the trail heads down to the valley.\n");
    add_item("castle","You can barely see it from this distance, but "+
    "it does look like some sort of castle or fortress.\n");
    add_exit(MTRAIL_DIR + "mtrail_path1", "north", 0, 2);
    add_exit(MTRAIL_DIR + "mtrail06", roadWest, "@@down", 2);
    add_exit(MTRAIL_DIR + "mtrail08", roadEast, 0, 2);
    
    add_npc("/d/Faerun/highroad/npcs/travelling_blacksmith", 1);
}

int
block()
{
    write("The trail blocked by a tretcherous-looking rock slide. " +
        "It seems impassable at this moment.\n");
    say(QCTNAME(TP)+" tries to go north but fails.\n");
    return 1;
}
