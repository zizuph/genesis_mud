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
    set_short("The back corridor");
    set_long("This is commonly referred to as the back corridor " +
        "as it leads outside to the east end of the valley. A " +
        "cool breeze floats in from the east porch.  West " +
        "leads into the house. The walls are off-white with " +
        "lamps spaced evenly across them. Wooden pillars divide " +
        "the walls into sections.\n");
 
    add_item(({"pillars", "square pillars", "square wooden pillars"}),
        "The pillars are carved from thick trees. They are squared " +
        "and are set into the walls. The pillars are expertly " +
        "decorated with carved leaves.\n");
    add_item(({"porch", "back porch",}),
        "The porch is covered and faces the east side of the " +
        "valley.\n");
    set_extra_window("@@window_position@@ set into the " +
        "east wall.");
    add_item(({"east windows", "eastern windows", "east window",
        "eastern windows"}), "@@east_down@@\n");

    num_of_windows=2;

 
    add_exit(VALLEY_DIR + "e_porch", "east");
    add_exit(VALLEY_DIR + "d_cor05", "west");
}
