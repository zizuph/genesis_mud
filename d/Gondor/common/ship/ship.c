/* ship.c

   Modified:
   Oct 1997 by Fysix: adjusted board function for steeds.
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/ship";
#include <cmdparse.h>
#include "/d/Gondor/defs.h"

void
create_ship()
{
    object cap;    
    seteuid(getuid());
    set_cabin(SHIP_DIR + "cabin");
    set_deck(SHIP_DIR + "deck");
    cap = clone_object(SHIP_DIR + "captain1");
    cap->arm_me();
    set_captain(cap);
    set_places_to_go(({PELAR_DIR + "docks/dock5",
		       ANDUIN_DIR + "pelargir",
                       ANDUIN_DIR + "mouth",
                       BAY_DIR + "eshore2",
                       BAY_DIR + "openwater",
                       BAY_DIR + "openwater2",
                       BAY_DIR + "openwater3",
		       "/d/Genesis/start/human/town/pier2",
                 BAY_DIR + "openwater3",
                 BAY_DIR + "openwater2",
                 BAY_DIR + "openwater",
                 BAY_DIR + "eshore2",
                 ANDUIN_DIR + "mouth",
		       ANDUIN_DIR + "pelargir",}));
    set_time_between_stops(({24,
			     3,
                             3,
                             3,
                             3,
                             3,
                             3,
                            24,
                             3,
                             3,
                             3,
                             3,
                             3,
		 	     3}));
    set_ticket_id("the Gondorian line");
    set_name("ship");
    add_name("boat");
    add_name("cog");
    add_adj("large");
    add_adj("merchant");
    set_long("This is a large ocean-going merchant cog, built of strong wood. "+
      "You see 15 oars sticking out on one side, and guess the number is "+
      "the same on the other side. A large, whiteish sail is set above the "+
      "ship, and embroidered on the sail you see a white tree surrounded by "+
      "seven silver stars.\n");
    enable_reset();
}

void
reset_ship()
{
    object cap;
    if (!objectp(query_captain()))
    {
	cap = clone_object(SHIP_DIR + "captain1");
	cap->arm_me();
	set_captain(cap);
	cap->move_living("down", query_deck()[0]);
	start_ship(location);
    }
}

int
board(string what)
{
    object ticket, *tmp;

    if (!board_enabled)
	return 0;

    if (what && (!sizeof(tmp =
                FIND_STR_IN_OBJECT(what, environment(TP))) ||
               TO != tmp[0]))
	return 0;

    if (TP->query_average_stat() >= 20)
	return ::board(what);

    // Added a check to see if player can board, Fysix, October 1997
    if (!query_cannot_board_ship(TP, query_deck()[0]))
    {
        write("You board the ship.\n");
        environment(TP)->set_dircmd(what);
        TP->move_living("boarding the ship", query_deck()[0]);
    }
    return 1;
}
