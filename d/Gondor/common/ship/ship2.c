/* /d/Gondor/common/ship/ship2.c
 *
 * Modified:
 * Oct 1997 by Fysix: adjusted board function for steeds.
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
    set_cabin(SHIP_DIR + "cabin2");
    set_deck(SHIP_DIR + "deck2");
    cap = clone_object(SHIP_DIR + "earendil");
    cap->arm_me();
    set_captain(cap);
    set_places_to_go(({PELAR_DIR + "docks/dock3",
		       ANDUIN_DIR + "pelargir",
                       ANDUIN_DIR + "mouth",
                       BAY_DIR + "eshore2",
                       BAY_DIR + "openwater",
                       BAY_DIR + "openwater2",
                       BAY_DIR + "openwater3",
                       BAY_DIR + "pt_macdunn1",
                       BAY_DIR + "pt_macdunn2",
//		       "/d/Genesis/start/elf/room/outside_harbour_2",
//		       "/d/Genesis/start/elf/room/outside_harbour_1",
		       "/d/Khalakhor/ship/macdunn/pier10",
                        BAY_DIR + "pt_macdunn2",
                        BAY_DIR + "pt_macdunn1",
//		       "/d/Genesis/start/elf/room/outside_harbour_1",
//		       "/d/Genesis/start/elf/room/outside_harbour_2",
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
                             3,
                             3,
                            24,
                             3,
                             3,
                             3,
                             3,
                             3,
                             3,
                             3,
		 	     3}));
    set_ticket_id("Earendil Shipping Service");
    set_name("ship");
    add_name("boat");
    add_name("vingilot");
    add_name("foam-flower");
    add_name("rothinzil");
    add_adj("slim");
    add_adj("sailing");
    set_long("This is the ship Vingilot, the Foam-flower. It is a beautiful " +
      "ocean-going sailing ship, built of strong white wood. "+
      "A large silver sail is set above the ship, and embroidered on the sail you see a golden star. "+
      "The prow of the ship is fashioned like a swan.\n");
    enable_reset();
}

void
reset_ship()
{
    object cap;
    if (!objectp(query_captain()))
    {
	cap = clone_object(SHIP_DIR + "earendil");
	cap->arm_me();
	set_captain(cap);
	cap->move(query_deck()[0]);
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
