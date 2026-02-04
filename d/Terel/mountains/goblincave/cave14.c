/*
 * cave14.c
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
        "The stones in the cave are black and slippery. " +
        "You sense the presence of danger nearby.\n");

    add_item(({"stones", "stone"}),
        "The stones are made of ordinary rock.\n");

    DARK;

    add_exit(MOUNTAIN_DIR + "goblincave/cave15", "east");
    add_exit(MOUNTAIN_DIR + "goblincave/cave03", "south");

    add_npc(MOUNTAIN_DIR + "goblincave/npc/std_goblin", 2);
}
