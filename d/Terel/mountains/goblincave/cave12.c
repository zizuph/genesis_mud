/*
 * cave12.c
 *
 * A cave room.
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
        "The eastern tunnel is damp and hot. Small fireflies "+
        "behind a glass window emit a calm, yellow light.\n");

    add_item("fireflies",
        "You stop to look at the dazzling dance of the fireflies.\n");

    add_item(({"window", "glass", "glass window"}),
        "It is securely embedded in the wall.\n");

    add_exit(MOUNTAIN_DIR + "goblincave/cave07", "west");
    add_exit(MOUNTAIN_DIR + "goblincave/cave08", "northwest");
    add_exit(MOUNTAIN_DIR + "goblincave/cave11", "east");

    add_npc(MOUNTAIN_DIR + "goblincave/monster/wolf");
    add_npc(MOUNTAIN_DIR + "goblincave/npc/std_goblin");
}
