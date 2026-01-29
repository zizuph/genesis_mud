/*
 * Great Arch in Moria from West-gate
 * By Finwe, February 2003
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "defs.h"

inherit BASE_ROOM;

void
create_mine_room()
{
    LIGHTS_OFF;
    set_area("in");
    set_areaname("the mines");
    set_land("Khazad-dum");
    set_areatype(0);
    set_areadesc("great arch");
    
    add_my_desc("This is where the stairs leading to the West-Gate " +
        "join the tunnels of Moria. This large hall leads runs north " +
        "to the tunnels of Khazad-dum and south to the stairs leading " +
        "down to the West-Gate. It is wide and at one time probably " +
        "grand, yet now it is dark and cold. Corpses line the walls, a " +
        "sign that a great battle was fought here. A great arch is set " +
        "into the north wall.\n");

    set_add_walls("");
    set_add_ceiling("");
    set_add_floor("");
    set_add_west_gate_stairs("");
    add_item(({"great arch", "arch"}),
        "The Great Arch marks the western entrance of Khazad Dum. " +
        "Once a grand marker, it is now chipped and cracked. The arch is " +
        "carved from the living rock of the mountain and stands as a " +
        "memorial to the dwarves who once lived here. The top is " +
        "semi-circular in shape, and the whole arch is wide enough to allow " +
        "probably twenty dwarves to walk abreast through it. A large " +
        "keystone is set at the top of the arch.\n");
    add_item(({"keystone"}),
        "The keystone, set at the top of the arch, is triangular shaped. " + 
        "A large silver star is carved into the center of the stone. A " +
        "crack runs down through it, but the stone looks stately, " +
        "nonetheless.\n");

    NORTH(DEEP1_DIR + "tunc07");
    DOWN(DEEP1_DIR + "stairs11");

}
