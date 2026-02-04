/*
 * cave18.c
 *
 * lower level of the goblin cave
 *
 * Lucius - Jan 2021
 *   Cleaned up and modernized.
 */
#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "goblincave/cave_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_terel_room()
{
    ::create_terel_room();
    set_long(query_long() +
        "The room appears to be cleaner than the rooms above.\n");

    DARK;

    add_exit(MOUNTAIN_DIR + "goblincave/cave17", "south");
    add_exit(MOUNTAIN_DIR + "goblincave/cave19", "east");
}
