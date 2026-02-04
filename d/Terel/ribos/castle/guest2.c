/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * guest2.c
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit CASTLE_DIR + "guest_room";

/*
 * Function name: room_search
 * Description:   called when the player seacrhes here.
 * Arguments:     player - the player who searches
 *                str    - what they search
 * Returns:       The message the player will should see.
 */
public string
room_search(object player, string str)
{
    if (clue_found == 0)
	if (str == "bed") {
	    FIX_EUID;
	    clone_object(CASTLE_DIR + "obj/clue2")->move(player);
	    clue_found = 1;
	    return "You look under the covers, inside the pillows, and look " +
		"underneath the bed.  Finally, you check in between the " +
		"mattress and box spring, finding a handwritten scroll.\n";
	}
    return("You didn't find anything of value.\n");
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    FIX_EUID;
    clone_object(DOOR_DIR + "guest2_out")->move(TO);
}
