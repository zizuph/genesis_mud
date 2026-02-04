/*
 * tcave07.c
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
        "South will lead you back towards the entrance of the cave.\n");

    add_exit(TROLL_CAVE_DIR + "tcave08", "north");
    add_exit(TROLL_CAVE_DIR + "tcave05",   "south");

    add_object("/d/Shire/common/obj/random_rock", random(3) + 2);
    add_object(TROLL_CAVE_DIR + "obj/bones");
    add_npc(TROLL_CAVE_DIR + "npc/troll", 2);
}
