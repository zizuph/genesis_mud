/*
 * tcave02.c
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
        "You can head farther into the cave by heading northwest "+
        "or return to the mouth of the cave, south.\n");

    add_exit(TROLL_CAVE_DIR + "tcave03", "northwest","@@guarded");
    add_exit(TROLL_CAVE_DIR + "tcave01", "south","@@guarded");
    add_exit(TROLL_CAVE_DIR + "tcave09", "north","@@guarded" );

    add_npc(TROLL_CAVE_DIR + "npc/troll", 3);
    add_object("/d/Shire/common/obj/random_rock", random(3) + 2);
}
