/*
 * cave05.c
 *
 * A cave room near the entrance that is home to two young orcs.
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
    set_long(query_long() +
        "This is a fairly small intersection. The ground is " +
        "covered with many footprints.\n");

    add_item("footprints",
             "There are several types.\n"+
             "You manage to recognize the ones from orcs and wolves.\n"+
             "There is also a third and bigger animal-type print " +
             "with 10 cm claws.\n");

    DARK;

    add_exit(MOUNTAIN_DIR + "goblincave/cave03", "north");
    add_exit(MOUNTAIN_DIR + "goblincave/cave04", "west");
    add_exit(MOUNTAIN_DIR + "goblincave/cave06", "south");

    add_npc(MOUNTAIN_DIR + "goblincave/npc/std_goblin", 2);
}
