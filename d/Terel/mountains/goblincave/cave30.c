/*
 * cave30.c
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
        "The tunnel ends in what looks like a makeshift barracks. "+
        "There are several mats laying on the ground here.\n");

    add_item("mats",
        "Mats which have been woven together out of straw.\n");

    DARK;

    add_exit(MOUNTAIN_DIR + "goblincave/cave29","west");

    add_npc(MOUNTAIN_DIR + "goblincave/npc/std_goblin", 3);
}
