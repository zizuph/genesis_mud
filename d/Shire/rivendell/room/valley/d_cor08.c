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
    set_short("A downstairs corridor");
    set_long("The corridor is wide here where it intersects with " +
        "another corridor. The rather plain off-white colored " +
        "walls are broken into sections by the square " +
        "shaped wooden pillars. The pillars are tall and " +
        "support the ceiling. The corridor continues north, " +
        "south, and west while south is a private guestroom.\n");
 
    add_item(({"pillars", "square pillars", "square wooden pillars"}),
        "The pillars are carved from thick trees. They are squared " +
        "and are set into the walls. The pillars are expertly " +
        "decorated with carved leaves.\n");
    add_item(({"sections", "panels"}),
        "Thesea  are the areas between the pillars. They are " +
        "without decoration.\n");
    add_item(({"private guestroom", "guestroom"}),
        "it appears to be occupied as you can see stuff all " +
        "over the place in there.\n");
 
    add_exit(VALLEY_DIR + "d_cor05", "north");
    add_exit(VALLEY_DIR + "bilbo_rm", "south");
    add_exit(VALLEY_DIR + "d_cor09", "east");
    add_exit(VALLEY_DIR + "d_cor07", "west");
}
