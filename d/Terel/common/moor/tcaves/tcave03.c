/*
 * tcave03.c
 *
 * Lucius - Jan 2021
 *    Modernized
 */
#include "/d/Terel/include/Terel.h"
inherit TROLL_CAVE_DIR + "tcave_room";
/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_terel_room()
{
    ::create_terel_room();
    set_long(query_long() +
        "You can head farther into the cave by heading northwest or north. "+
        "South will lead you back towards the entrance of the cave.\n");

    add_exit(TROLL_CAVE_DIR + "tcave05", "north");
    add_exit(TROLL_CAVE_DIR + "tcave04", "northwest");
    add_exit(TROLL_CAVE_DIR + "tcave02", "southeast");

    add_npc(TROLL_CAVE_DIR + "npc/troll", 2);
}
