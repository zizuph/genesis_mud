/*
 * cave22.c
 *
 * A cave room that is the chamber of the goblin lord
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
        "This cave is sparsely furnished with a round stone table "+
        "and a stone throne. It is clearly inhabited by an " +
        "important person.\n");

    add_item("table", "There is nothing on it.\n");

    add_item("throne",
        "You see that it is carved right out of the stonewalls.\n");

    add_exit(MOUNTAIN_DIR + "goblincave/cave19", "west");
    add_npc(MOUNTAIN_DIR + "goblincave/npc/goblinlord");
}
