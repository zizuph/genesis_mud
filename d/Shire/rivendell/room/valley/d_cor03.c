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
    set_short("The front corridor");
    set_long("You're in the front corridor, outside the Hall of " +
        "Fire and Elrond's study. It is wide and spacious with " +
        "square wooden pillars evenly spaced along the walls. " +
        "The pillars are set into the walls and support " +
        "the ceiling. The walls are an off-white color with " +
        "lamps evenly spaced on them.\n");
 
    add_item(({"pillars", "square pillars", "square wooden pillars"}),
        "The pillars are carved from thick trees. They are squared " +
        "and are set into the walls. The pillars are expertly " +
        "decorated with carved leaves.\n");
    add_item("bridge",
        "The bridge spans a the river west of here. The path " +
        "crosses it as it continues into the mountains.\n");
    add_item(({"porch", "front porch",}),
        "The porch is covered and faces the west side of the " +
        "valley.\n");

    set_extra_window("@@window_position@@ set into the " +
        "east wall.");
    add_item(({"east windows", "eastern windows", "east window",
        "eastern windows"}), "@@east_down@@\n");

    num_of_windows=2;

 
    add_exit(VALLEY_DIR + "fire",        "north");
    add_exit(VALLEY_DIR + "elrond_hall", "south");
    add_exit(VALLEY_DIR + "d_cor04",     "east");
    add_exit(VALLEY_DIR + "w_porch",     "west");
}
