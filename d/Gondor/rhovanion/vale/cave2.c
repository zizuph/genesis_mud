#include "../defs.h"

inherit RHOVANION_STD_DIR + "room";
inherit "/d/Gondor/common/lib/herbsearch";
inherit RHOVANION_DIR + "mirkwood/std/warning";
inherit "/d/Gondor/common/lib/room_tell";

#include <macros.h>

void

create_room()
{
    set_short("Base of the Carrock");
    set_long("This is a very small and dark, yet surprisingly dry and " +
        "wholesome looking, cave. Thousands of pebbles line the floor " +
        "of the cave, and the smooth walls slope upwards, joining high " +
        "overhead in a rounded ceiling. To the east, you can see the " +
        "rushing waters of a river running over some flat, black stones " +
        "which lead to the opposite bank of the river.\n");

    add_item(({"grasses", "grass", "ground", "field", "fields", "green grass",
            "yellowish grass", "yellow grass", "yellow-green grass"}),
        "The other side of the river is full of a tall, yellow-green grass " +
        "which sways in the wind with every breeze which blows past.\n");
    add_item(({"bank", "river bank"}),
        "The river bank is filled with a tall green grass which sways and " +
        "bends in the wind.\n");
    add_item(({"cave", "small cave", "dark cave"}),
        "This is a very small and dark, yet surprisingly dry and " +
        "wholesome looking, cave. Thousands of pebbles line the floor " +
        "of the cave, and the smooth walls slope upwards, joining high " +
        "overhead in a rounded ceiling. To the east, you can see the " +
        "rushing waters of a river running over some flat, black stones " +
        "which lead to the opposite bank of the river.\n");
    add_item(({"pebble", "pebbles", "ground", "floor", "down"}),
        "The ground here is filled with thousands of smooth, rounded " +
        "pebbles. The floor is surprisingly dry when you notice that there " +
        "is a river running right past the mouth.\n");
    add_item(({"mouth", "opening", "edge", "edges"}),
        "The mouth of the cave is not very large, but the edges are smooth " +
        "and rounded.\n");
    add_item(({"wall", "walls"}),
        "The walls here are very smooth and dry, giving this cave a sort of " +
        "wholesome feeling.\n");
    add_item(({"up", "ceiling"}),
        "The ceiling above is smooth and rounded, free of any stalactites " +
        "you might have expected to see.\n"); 
    add_item(({"path", "stones", "flat stones", "black stones"}),
        "These black stones are rather flat, and rise up just about the " +
        "surface of the water. There seems to be a line of them, winding a " +
        "path from the the Carrock to the eastern bank of the Anduin " +
        "river.\n");
    add_item(({"river", "water", "waters", "anduin", "anduin river"}),
        "These swirling blue waters rushing past are part of the great " +
        "Anduin river, which flows southward towards the sea.\n"); 

    add_exit(VALE_DIR + "cave1", "east", 0,2,0);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

}
