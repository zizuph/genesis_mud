/*
 * 920818: Modified by dust to include fire (mini-quest)
 * and hint for the big quest.
 */
/*
 * cave11.c
 *
 * A cave room that is the chamber of the orc chief and also has the fire
 * which is a subquest of zodiac.
 *
 * Lucius - Jan 2021
 *   Cleaned up and modernized.
 */

#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "goblincave/cave_room";

#include "/d/Terel/include/zodiac.h"

/*
 * It contains a hint for the secret door
 * There are several hints spread, this is
 * hint number HINT_INDEX
 */
#define HINT_INDEX 1

/*
 * this_hint is the hint stored in this room
 */
#define this_hint (calc_hint(1))

/*
 * Function name: query_real_hint
 * Description:   return the hint for the zodiac quest.
 * Returns:       the zodiac quest hint number.
 */
nomask int
query_real_hint()
{
    return this_hint;
}


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_terel_room()
{
    ::create_terel_room();
    set_long(query_long() +
        "This cave is basically barren.\n");

    add_exit(MOUNTAIN_DIR + "goblincave/cave10", "north");
    add_exit(MOUNTAIN_DIR + "goblincave/cave12", "west");

    add_object(ZODIAC_DIR + "fire");
}

/*
 * Function name: reset_room
 * Description:   Fix the fire and the orcchief at each reset.
 */
public void
reset_terel_room()
{
    object temp;

    if (temp = present("Zodiac:ash"))
        temp->remove_object();
    if (temp = present("Zodiac:coal"))
        temp->remove_object();
    if (temp = present("Zodiac:glow"))
        temp->remove_object();
}

/*
 * Function name: smell_desc
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */
public void
hook_smelled(string str)
{
    if (!strlen(str))
    {
        write("There is a faint smell foul creatures "+
            "and a trace of dog.\n");
    }
}

