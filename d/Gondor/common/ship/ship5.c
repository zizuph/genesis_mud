/* ship.c

   Modified:
   Oct 1997 by Fysix: adjusted board function for steeds.
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/ship.c";

#include <cmdparse.h>

#include "/d/Gondor/defs.h"

public void
create_ship()
{
    object cap;    
    seteuid(getuid());
    set_cabin(SHIP_DIR + "cabin5");
    set_deck(SHIP_DIR + "deck5");
    cap = clone_object(SHIP_DIR + "captain5");
    cap->arm_me();
    set_captain(cap);
    set_places_to_go(({PELAR_DIR + "docks/dock7",
		       ANDUIN_DIR + "pelargir",
                       ANDUIN_DIR + "mouth",
                       BAY_DIR + "eshore2",
                       BAY_DIR + "openwater",
                       BAY_DIR + "openwater2",
                       BAY_DIR + "openwater3",
		       "/d/Kalad/common/port/s100",
                       BAY_DIR + "openwater3",
                       BAY_DIR + "openwater2",
                       BAY_DIR + "openwater",
                       BAY_DIR + "eshore2",
                       ANDUIN_DIR + "mouth",
	 	       ANDUIN_DIR + "pelargir",}));
    set_time_between_stops(({15,
			     3,
                             3,
                             3,
                             3,
                             3,
                             3,
                            15,
                             3,
                             3,
                             3,
                             3,
                             3,
		 	     3}));
    set_ticket_id("The Gondor - Kalad trade-line");
    set_name("ship");
    add_name("boat");
    add_adj("large");
    add_adj("merchant");
    set_long(break_string("Moored here is a large merchant ship, that currently " +
        "sails from Gondor to Kalad and back on a regular basis. Due to the " +
        "fear of Corsairs off the Gondorian coastline, the merchant ship "+
        "sails at irregular times. The boat looks like it has been sailing for "+
        "some years, but it still seems quite safe and sturdy. "+
       "There are various items, like ropes, lying here.\n", 78));
    enable_reset();
}

void
reset_ship()
{
    object cap;
    if (!objectp(query_captain()))
    {
	cap = clone_object(SHIP_DIR + "captain5");
	cap->arm_me();
	set_captain(cap);
	cap->move_living("down", query_deck()[0]);
	sail_away_out_on_the_open_sea();
    }
}

int
board(string what)
{
    object ticket, *tmp;

    if (!board_enabled)
   return 0;
    if (what && (!sizeof(tmp =
                FIND_STR_IN_OBJECT(what, ENV(TP))) ||
               TO != tmp[0]))
   return 0;
    if (TP->query_average_stat() >= 20)
   return ::board(what);

    // Added a check to see if player can board, Fysix, October 1997
    if (!query_cannot_board_ship(TP, query_deck()[0]))
    {
        write("You board the ship.\n");
        ENV(TP)->set_dircmd(what);
        TP->move_living("boarding the ship", query_deck()[0]);
    }

    return 1;
}
