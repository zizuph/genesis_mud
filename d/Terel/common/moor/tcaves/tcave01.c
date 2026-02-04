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
        "You can head farther into the cave by heading north or "+
        "return to the mouth of the cave, south.\n");
    
    add_exit(TROLL_CAVE_DIR + "tcave02",  "north", "@@guarded");
    add_exit(TROLL_CAVE_DIR + "entrance", "south", 0);
    
    add_object(TROLL_CAVE_DIR + "obj/bones", random(2) + 1);
    add_object(TROLL_CAVE_DIR + "obj/twigs", random(2) + 1);
    add_npc(TROLL_CAVE_DIR + "npc/troll", 3);
}
