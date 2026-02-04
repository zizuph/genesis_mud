/* This comment tells emacs to use c++-mode -*- C++ -*- */

#include "/d/Terel/include/Terel.h"
inherit "/d/Genesis/ship/ship";

#define SPARKLE  "/d/Genesis/start/human/town/pier5"
#define SHIP_NAME     "Calathin Commoner"
#define DAB_HARB    DABAAY_DIR + "harbor/"


/*
 * Function name: create_ship
 * Description	: Create the ship
 */
public void
create_ship()
{
    object captain;
    
    FIX_EUID;
    set_cabin(SHIP_DIR + "t_cabin");
    set_deck(SHIP_DIR + "t_deck");
    captain = clone_object(SHIP_DIR + "t_captain");
    set_captain(captain);
    set_places_to_go(({DAB_HARB + "spier_3",
		       SHIP_DIR + "bay",
		       SHIP_DIR + "sea1",
		       SHIP_DIR + "sea2",
		       SHIP_DIR + "sea3",			   
		       SPARKLE,
		       SHIP_DIR + "sea3",			     
		       SHIP_DIR + "sea2",
		       SHIP_DIR + "sea1",
		       SHIP_DIR + "bay"}));
    set_time_between_stops(({25,
			     3,
			     12,
			     5,
			     5,
			     25,
			     5,
			     5,
			     12,
			     3}));
    set_ticket_id("the Terel-Sparkle line");
    set_name("ship");
    add_name("boat");
    set_adj(({"large", "sailing"}));
    set_short("large sailing ship");
    set_long("It's a large sailing ship. On the side of the ship you " +
	     "read the name: " + SHIP_NAME + ".\n");
}
