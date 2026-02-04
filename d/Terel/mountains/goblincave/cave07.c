/*
 * cave07.c
 *
 * A cave room that is home to two orc guards.
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
        "This room is a little bigger than the others. " +
        "@@longdesc@@");

    DARK;

    add_exit(MOUNTAIN_DIR + "goblincave/cave06", "west");
    add_exit(MOUNTAIN_DIR + "goblincave/cave08", "northeast");
    add_exit(MOUNTAIN_DIR + "goblincave/cave12", "east");

    add_npc(MOUNTAIN_DIR + "goblincave/npc/std_goblin_grd");
    add_object("/d/Shire/common/obj/random_rock", random(3) + 2);
}

/*
 * Function name: longdesc
 * Description:   Change the long desc of the room to reflect the presence
 *                or absence of the orcguard.
 * Returns:       The string with the description.
 */
public string
longdesc()
{
    if (present("_terel_cave_goblin"))
        return "The heavily equipped guard is doing some shadow-fencing.\n";

    return "It looks like there has been a lot of fighting here lately.\n";
}
