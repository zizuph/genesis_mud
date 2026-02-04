/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * gate_ent.c
 *
 *  This is the front entry foyer to the Ribos Castle.  It will have
 *  various cosmetic descriptions that will tie in to a quest, and will
 *  also have a guard that starts here, but will wander around the
 *  castle
 *
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDROOM;

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({CASTLE_DIR + "monster/okayguard"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    set_short("Castle gates");
      
    set_long("You have entered a large tunnel running through the " +
	     "great wall of the Castle of Ribos.  Its stones are white in " +
	     "color, and shine even under the tunnel.  There are a set of " + 
	     "large, strong silver gates to your south, which are almost " +
	     "always open.  To your north, you see a majestic courtyard, " +
	     "with well kept shrubs and freshly cut grass.\n");

    add_item(({"gate", "silver gate", "gates", "silver gates",
		   "castle gates"}),
	     "They are made from pure silver, and they reflect the " +
	     "sunlight well.  The servants\nmust polish these things " +
	     "very often.\n");

    add_item(({"courtyard", "yard", "court"}),
	     "This is a fine green lawn with several buildings " +
	     "surrounding it.  The shrubs\nare well kept, and you " +
	     "can see several knights practicing there.\n");

    add_item(({"castle", "castle of Ribos", "castle of ribos"}),
	     "A Fine castle, constructed from white blocks of " +
	     "rock like you've never seen\nbefore.  Along with " +
	     "the bright colors of the rooftops, it is one of the " +
	     "most beautifull castles in existence.\n");

    add_item(({"stones", "white stones"}),
	     "These stones look very clean around the edges, as " +
	     "if they were cut from a mountanside only days ago.  " +
	     "They really reflect the daylight well.\n");

    add_exit(CASTLE_DIR + "cas_ent", "south", 0);
    add_exit(CASTLE_DIR + "court",   "north", 0);

    clone_object(DOOR_DIR + "gate_w_in")->move(TO);
    clone_object(DOOR_DIR + "gate_e_in")->move(TO);
    reset_room();
}
 
