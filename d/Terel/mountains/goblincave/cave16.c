/*
 * cave16.c
 *
 * lower level of the goblin cave
 *
 * Lucius - Jan 2021
 *   Cleaned up and modernized.
 */
#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "goblincave/cave_room";

#include <ss_types.h>
#include <stdproperties.h>

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

    add_exit(MOUNTAIN_DIR + "goblincave/cave13", "up");
    add_exit(MOUNTAIN_DIR + "goblincave/cave17", "east");

    add_npc(MOUNTAIN_DIR + "goblincave/npc/std_goblin_grd");
    add_npc(MOUNTAIN_DIR + "goblincave/npc/std_goblin");
}
