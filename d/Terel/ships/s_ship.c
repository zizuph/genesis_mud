/* This comment tells emacs to use c++-mode -*- C++ -*- */

#include "/d/Terel/include/Terel.h"
#include <cmdparse.h>   /* FIND_STR_IN_OBJECT macro */

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
    set_cabin(SHIP_DIR + "s_cabin");
    set_deck(SHIP_DIR +  "s_deck");
    captain = clone_object(SHIP_DIR + "s_captain");
    set_captain(captain);
    set_places_to_go(({DAB_HARB + "spier_2",
		       SHIP_DIR + "bay",
		       SHIP_DIR + "river1",
		       SHIP_DIR + "river2",
		       SHIP_DIR + "river3",
		       SHIP_DIR + "river4",
		       SHIP_DIR + "river5",
		       SHIP_DIR + "river6",
		       SHIP_DIR + "river7",
		       SHIP_DIR + "river8",
		       SHIP_DIR + "river9",
		       SHIP_DIR + "glade",
		       SHIP_DIR + "river9",
		       SHIP_DIR + "river8",
		       SHIP_DIR + "river7",
		       SHIP_DIR + "river6",
		       SHIP_DIR + "river5",
		       SHIP_DIR + "river4",
		       SHIP_DIR + "river3",
		       SHIP_DIR + "river2",
		       SHIP_DIR + "river1",
		       SHIP_DIR + "bay"}));
    set_time_between_stops(({12,
			      4,
			      4,
			      4,
			      4,
			      4,
			      4,
			      4,
			      4,
			      4,
			      4,
			     12,
			      3,
			      3,
			      3,
			      3,
			      3,
			      3,
			      3,
			      3,
			      3,
			      4}));
    
    set_ticket_id("the Terel pier-to-pier line");
    set_name("boat");
    add_name("fishing boat");
    add_name("ship");
    set_adj("small");
    add_adj("fishing");
    set_long("A small fishing boat. Nowadays this fishing boat is " +
	     "used to transport people across the bay; that is, " +
	     "between the eastern and western piers. It also " +
	     "goes upriver.\n");
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
