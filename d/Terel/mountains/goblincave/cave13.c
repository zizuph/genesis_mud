/*
 * cave13.c
 *
 * An empty room in the cave.  The entrance to the cave lower level is here.
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
        "In the corner of the cavern is a small tunnel "+
        "leading downwards.\n");

    DARK;

    add_exit(MOUNTAIN_DIR + "goblincave/cave09", "west");
    add_exit(MOUNTAIN_DIR + "goblincave/cave15", "northwest");
    add_exit(MOUNTAIN_DIR + "goblincave/cave16", "down");

    add_npc(MOUNTAIN_DIR + "goblincave/npc/std_goblin_grd", 2);
    add_npc(MOUNTAIN_DIR + "goblincave/npc/std_goblin", 2);
}
