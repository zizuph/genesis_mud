/*
 * /d/Rhovanion/common/rhun/camp/room.c
 *
 * Base room for the barbarian camp.
 */

#include <filter_funs.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"

inherit "/d/Rhovanion/lib/room";

/* MaxBar is the maximum number of barbarians that
 * can be in the room at the same time.
 */

int MaxBar = 0;
string MonsterFile = "npc/barbarian";

/*
 * Function name: trygo
 * Description:   Check if there are any barbarians in the room, and
 *                if so, return 1, thereby preventing movement. Used
 *                as parameter 3 of add_exit.
 * Arguments:     (none)
 * Returns:       0 if it's ok to move, 1 if not.
 */

int
try_go()
{
    if (TP->query_invis() != 0)
        return 0;

    if (present("_barbarian_", TO) ||
        present("chief", TO))
    {
        tell_room(TO, QTNAME(TP) + " tries to go " + query_verb() +
                  ", but is stopped by a barbarian.\n", TP);
        write("The barbarian won't let you go " + query_verb() + "!\n");
        return 1;
    }

    return 0;
}

/*
 * Function name: reset_camp
 * Description:   Clone n barbarians, 1 <= n <= MaxBar. There can only
 *                be MaxBar barbarians in the room at a time.
 * Arguments:     (none)
 * Returns:       (void)
 */

void
reset_camp()
{
    object  *list;
    object  dummy;
    int     i, friends, number_to_clone;

    friends = 0;
    list = FILTER_LIVE(all_inventory(TO));
    for (i = 0; i < sizeof(list); i++)
    {
        if ((list[i]->query_name() == "_barbarian_") ||
            (list[i]->query_name() == "Chief"))
            friends++;
    }

    number_to_clone = MaxBar / 2 + random((MaxBar + 1) / 2 + 1); 

    for (i = friends; i < number_to_clone; i++)
    {
        dummy = clone_object(CAMP_DIR + MonsterFile);
        dummy->arm_me();
        dummy->move(TO);
    }
}

/*
 * Function name: reset_room
 * Description:   Resets the room by calling reset_camp.
 * Arguments:     (none)
 * Returns:       (void)
 */

void
reset_room()
{
    reset_camp();
}

/*
 * Function name: create_camp
 * Description:   Dummy function for overriding.
 * Arguments:     (none)
 * Returns:       (void)
 */

void
create_camp()
{

}

/*
 * Function name: create_room
 * Description:   Creates the room by calling create_camp, and then
 *                automatically calls reset_room().
 * Arguments:     (none)
 * Returns:       (void)
 */

void
create_room()
{
    create_camp();
    reset_room();
}

