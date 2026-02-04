/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * guest4.c
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
	if (str == "table" || str == "night table" || str == "nighttable") {
	    FIX_EUID;
	    clone_object(CASTLE_DIR + "weapon/clue4")->move(player);
	    clue_found = 1;
	    return "You open the night table, discovering an intricate " +
		"dagger.\n";
	    
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
    clone_object(DOOR_DIR + "guest4_out")->move(TO);
}
