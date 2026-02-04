/*
 * cave03.c
 *
 * A cave room near the entrance.
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
        "The room appears bare.\n");

    DARK;

    add_exit(MOUNTAIN_DIR + "goblincave/cave02", "west");
    add_exit(MOUNTAIN_DIR + "goblincave/cave05", "south");
    add_exit(MOUNTAIN_DIR + "goblincave/cave14", "north");
}
