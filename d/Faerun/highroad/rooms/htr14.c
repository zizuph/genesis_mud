/*
 * Mountain trail in the Sword Mountains
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_ROAD;

void
create_road()
{
    add_prop(ROOM_S_MAP_FILE, "sword_mt_map.txt");

    set_short("a barren knoll");
    set_extraline("The knoll is barren, and nothing grows here. In fact the ground is bare of anything except for a few rocks and a group of huts surrounding an ancient apparatus. The wind blows here, cutting like a knife, but snow doesn't accumulate. To the north are the remains of a hut.");

    add_item(({"huts"}),
        "They are made of wood and are crowded on the knoll. Why they are here is unknown, but they appear to be used. Faint ribbons of light shine through the chinks of the huts' walls.\n");
    add_item(({"wood"}),
        "The wood is weathered and makes up all the huts. It is stacked on top of each other, forming the walls and roofs. There are chinks in the walls where the wood is stacked.\n");
    add_item(({"chinks"}),
        "They are spaces between the wooden walls. Ribbons of light shine through them.\n");
    add_item(({"walls"}),
        "They are made of wood. The walls looks weathered and have chinks in them.\n");
    add_item(({"roof"}),
        "It is peaked and made of weathered wood.\n");
    add_item(({"ground", "down", "knoll"}),
        "It has been swept clean from the constant wind. The ground is dark brown and smooth.\n");
    add_item(({"mountains"}),
        "They are tall and surround the knoll. The mountains are rugged looking and topped with snow.\n");
    add_item(({"snow"}),
        "It covers the tops of the mountains that surround the knoll. However, none is visible here.\n");
    add_item(({"remains", "remains of a hut", "hut remains"}),
        "There was once a hut to the north, but it looks like it was pushed over the edge of the knoll by an avalanche. Now all that remains is a bare patch where it once stood.\n");

    add_room_tell("A cold wind blows across the knoll.");
    add_room_tell("The wind howls in your ears.");

    reset_faerun_room();
    
   // room_add_object("/d/Faerun/guilds/nov/obj/nexus_app");

    add_exit(HR_DIR + "hut_food", "northeast");
    add_exit(HR_DIR + "hut_leather", "east");
    add_exit(HR_DIR + "hut_potions", "northwest");
    add_exit(HR_DIR + "hut_bank", "west");
    add_exit(HR_DIR + "htr13", "south");

}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
}

int enter()
{
    TP->move_living("enters the hut.", HR_DIR + "nov_hut");
    return 1;

}