/* This comment tells emacs to use c++-mode -*- C++ -*- */

#include "/d/Terel/include/Terel.h"
inherit "/d/Genesis/ship/ship";

#define ELFSTART    "/d/Genesis/start/elf/room/"
#define SHIP_NAME   "Calathin Expeditioner"
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
    set_cabin(SHIP_DIR + "e_cabin");
    set_deck(SHIP_DIR + "e_deck");
    captain = clone_object(SHIP_DIR + "e_captain");
    set_captain(captain);
    set_places_to_go(({DAB_HARB + "npier_1",
		       SHIP_DIR + "bay",
		       SHIP_DIR + "sea1",
		       SHIP_DIR + "sea2",
		       ELFSTART + "outside_harbour_2",
		       ELFSTART + "outside_harbour_1",
		       ELFSTART + "cove_3",
		       ELFSTART + "outside_harbour_1",
		       ELFSTART + "outside_harbour_2",
		       SHIP_DIR + "sea2",
		       SHIP_DIR + "sea1",
		       SHIP_DIR + "bay"}));
    set_time_between_stops(({25,
			     3,
			     12,
			     5,
			     3,
			     5,
			     25,
			     5,
			     3,
			     5,
			     12,
			     3}));
    
    set_ticket_id("the Terel-elven line");
    set_name("ship");
    add_name("boat");
    set_adj(({"large", "sailing"}));
    set_short("large sailing ship");
    set_long("It's a large sailing ship. On the side of the ship you " +
	 "read the name: " + SHIP_NAME +".\n");
}
