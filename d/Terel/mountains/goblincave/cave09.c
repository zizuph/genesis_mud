/*
 * cave09.c
 *
 * A cave room that is home to two orc guards.
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
    set_long(query_long() + "\n");

    DARK;

    add_exit(MOUNTAIN_DIR + "goblincave/cave08", "south");
    add_exit(MOUNTAIN_DIR + "goblincave/cave10", "southeast");
    add_exit(MOUNTAIN_DIR + "goblincave/cave13", "east");

    add_npc(MOUNTAIN_DIR + "goblincave/npc/std_goblin_grd", 2);
}
