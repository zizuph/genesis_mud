/* This comment tells emacs to use c++-mode -*- C++ -*- */

#include "/d/Terel/include/Terel.h"
#include <cmdparse.h>
inherit "/d/Genesis/ship/ship";
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
    set_cabin(SHIP_DIR + "n_cabin");
    set_deck(SHIP_DIR + "n_deck");
    captain = clone_object(SHIP_DIR + "n_captain");
    set_captain(captain);
    set_places_to_go(({NPORT_DIR + "pier1",
 		       SHIP_DIR + "n_bay",
		       SHIP_DIR + "coast5",
		       SHIP_DIR + "coast4",
		       SHIP_DIR + "coast3",
		       SHIP_DIR + "coast2",
		       SHIP_DIR + "coast1",
		       SHIP_DIR + "bay",
		       DAB_HARB + "npier_2",
		       SHIP_DIR + "bay",
		       SHIP_DIR + "coast1",
		       SHIP_DIR + "coast2",
		       SHIP_DIR + "coast3",
		       SHIP_DIR + "coast4", 
		       SHIP_DIR + "coast5",
		       SHIP_DIR + "n_bay"}));
    set_time_between_stops(({12,
			      3,
			      4,
			      4,
			      4,
			      4,
			      4,
			      3,
			      12,
			      3,
			      4,
			      4,
			      4,
			      4,
			      4,
			      3}));
    set_ticket_id("the north and south port of Terel line");
    set_name("boat");
    add_name("passenger trawler");
    add_name("ship");
    set_adj("small");
    add_adj("passenger");
    set_long("A small passenger boat. Nowadays this boat is " +
	     "used to transport people across the continent; that is, " +
	     "between the northern and southern ports.\n");
}

public int board(string what)
{
    object ticket, *tmp;

    if (!board_enabled) return 0;

    if (what && (!sizeof(tmp = FIND_STR_IN_OBJECT(what, environment(TP))) ||
        this_object() != tmp[0]))
        return 0;

    if (this_player()->query_average_stat() >= 20) return ::board(what);

    write("You board the ship.\n");
    environment(TP)->set_dircmd(what);
    TP->move_living("boarding the ship", query_deck()[0]);
    return 1;
}
