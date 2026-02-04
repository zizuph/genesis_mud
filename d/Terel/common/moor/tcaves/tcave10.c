/*
 * tcave01.c
 *
 * A cave room near the entrance.
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
        "You have come to a dead end, the only way out is back towards" +
        " the south.\n");

    add_exit(TROLL_CAVE_DIR + "tcave09", "south");

    add_object(TROLL_CAVE_DIR + "obj/bones", random(2) + 1);
    add_object(TROLL_CAVE_DIR + "obj/twigs", random(2) + 1);
    add_npc(TROLL_CAVE_DIR + "npc/troll", 3);
}
