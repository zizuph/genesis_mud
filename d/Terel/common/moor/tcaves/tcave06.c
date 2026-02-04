/*
 * tcave06.c
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
        "You can head farther into the cave by heading northeast. "+
        "South will lead you back towards the entrance of the cave.\n");

    add_exit(TROLL_CAVE_DIR + "tcave08", "northeast");
    add_exit(TROLL_CAVE_DIR + "tcave04", "south");

    add_npc(TROLL_CAVE_DIR + "npc/troll");
}
