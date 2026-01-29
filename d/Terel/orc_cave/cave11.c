/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * 920818: Modified by dust to include fire (mini-quest)
 * and hint for the big quest.
 */

/*
 * cave11.c
 *
 * A cave room that is the chamber of the orc chief and also has the fire
 * which is a subquest of zodiac.
 */

#include "/d/Terel/include/Terel.h"
inherit ORC_CAVE_DIR + "cave_room";

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
create_room()
{
    ::create_room();
    set_long(query_long() + 
	     "This cave is sparsely furnished with a round stone table "+
	     "and a stone throne. It is clearly inhabited by an " +
	     "important person.\n");

    add_item("table", "There is nothing on it.\n");
    
    add_item("throne",
	     "You see that it is carved right out of the stonewalls.\n");

    add_exit(ORC_CAVE_DIR + "cave10", "north");
    add_exit(ORC_CAVE_DIR + "cave12", "west");
    add_exit(ORC_CAVE_DIR + "cave17", "east");
    
    reset_room();
}

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({ORC_CAVE_DIR + "monster/orcchief",
	     ZODIAC_DIR + "fire"});
}

/*
 * Function name: reset_room
 * Description:   Fix the fire and the orcchief at each reset.
 */
public void
reset_room()
{
    object temp;

    if (temp = present("ash"))
        temp->remove_object();
    if (temp = present("coal"))
        temp->remove_object();
    if (temp = present("glow"))
        temp->remove_object();

    ::reset_room();
}

/*
 * Function name: smell_desc
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */ 
public string
smell_desc()
{
    return "There is a faint smell foul creatures and an overpowering " +
	"smell of fire and sulfur.\n";
}

