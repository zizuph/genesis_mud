/*
 * cave37.c
 *
 * An empty room in the cave.
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
        "The caves continue deeper into the rock.\n");

    DARK;

    add_exit(MOUNTAIN_DIR + "goblincave/cave38","east");
    add_exit(MOUNTAIN_DIR + "goblincave/cave36","northeast");

    add_npc(MOUNTAIN_DIR + "goblincave/monster/wolf", 2);
}
