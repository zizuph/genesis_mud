/*
 * Sleeping room
 * Boreaulam, April 2012
 */
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#pragma strict_types

inherit L1_BASE_ROOM;

/*
 * Function name:		create_room
 * Description  :		creates room
 */
void
create_room()
{
	::create_room();
    set_short("Training room");

    set_long("Here you see many goblin warriors, practicing their skills. " +
	         "For a fee, you may <improve> your own skills also.  Perhaps you " +
	         "can <learn> a new skill here as well. There is a small opening " +
	         "in eastern wall." +
	         "\n\n");
	add_item(({"opening", "small opening", "eastern wall"}),
			 "You can see a small opening in the eastern wall. " +
             "Weapon clashes are heard from there.\n");
	add_item(({"warrior", "warriors"}),
			 "Some warriors are training here under supervision of more " +
             "experienced trainer.\n");

    add_exit ("roomf","west");
    add_exit ("roomh","north");

    add_npc(NPCS_DIR + "trainer", 1, &->arm_me());


    reset_room();
} /* create_room */

/*
 * Function name:		init
 * Description  :		init room
 */
void
init()
{
    ::init();
    add_action("enter", "enter", 0);
} /* init */


/*
 * Function name:		enter
 * Description  :		enters to roomi
 */
int
enter(string s)
{
    notify_fail("Enter what?\n");
    if(s!="" && s!="opening")
        return 0;

    set_dircmd("opening");
    TP->move_living("into the opening", ROOMS_DIR + "level1/roomi");
    return 1;
} /* enter */

