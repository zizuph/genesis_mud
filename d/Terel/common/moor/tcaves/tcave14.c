/*
 * tcave08.c
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
        "You have reached a large cavern. The main cavern of this lair. "+
        "The cave is a bit darker in the back. " +
        "You may only move in one direction from this room, south.\n");

    add_exit(TROLL_CAVE_DIR + "tcave12", "south", "@@guarded");

    add_object(TROLL_CAVE_DIR + "obj/bones", 2);
    add_npc(TROLL_CAVE_DIR + "npc/troll", 2);
    add_npc(TROLL_CAVE_DIR + "npc/gtroll");
}
