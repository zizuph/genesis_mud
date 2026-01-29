/*
 * Downstairs corridor
 * By Finwe, February 1998
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit HOUSE_IN_BASE;
 
void
create_house_room()
{
    set_short("A downstairs corridor outside the music room");
    set_long("You're in a corridor outside the music room. It " +
        "is wide and spacious with square wooden pillars are " +
        "evenly spaced along the walls. The pillars are set " +
        "into the walls and support the ceiling. The walls are " +
        "an off-white color with lamps evenly spaced on them.\n");
 
    add_item(({"pillars", "square pillars", "square wooden pillars"}),
        "The pillars are carved from thick trees. They are squared " +
        "and are set into the walls. The pillars are expertly " +
        "decorated with carved leaves.\n");
 
    add_exit(VALLEY_DIR + "music_rm", "north");
    add_exit(VALLEY_DIR + "d_cor04",  "south");
}
