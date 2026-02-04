/*
 * tcave05.c
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
        "You can head farther into the cave by heading north. "+
        "Southeast will lead you back towards the entrance of the cave.\n");

    add_exit(TROLL_CAVE_DIR + "tcave14", "north");
    add_exit(TROLL_CAVE_DIR + "tcave11", "south");

    add_object(TROLL_CAVE_DIR + "obj/bones", random(2) + 1);
    add_object(TROLL_CAVE_DIR + "obj/twigs", random(2) + 1);
    add_npc(TROLL_CAVE_DIR + "npc/troll", 3);
}
