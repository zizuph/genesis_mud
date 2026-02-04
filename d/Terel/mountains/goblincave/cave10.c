/*
 * cave10.c
 *
 * A cave room that is home to a large wolf.
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
        "The entrance to the southern room is covered with ornaments. " +
        "Small fireflies behind a glass window emit a calm, yellow " +
        "light.\n");

    add_item("fireflies",
        "You stop to look at the dazzling dance of the fireflies.\n");

    add_item(({"window","glass","glass window"}),
        "It is securely embedded in the wall.\n");

    add_exit(MOUNTAIN_DIR + "goblincave/cave09", "northwest");
    add_exit(MOUNTAIN_DIR + "goblincave/cave11", "south");

    add_npc(MOUNTAIN_DIR + "goblincave/npc/std_goblin_grd", 2);
}
