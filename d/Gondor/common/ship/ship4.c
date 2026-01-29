/* ship4.c

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
    set_cabin(SHIP_DIR + "cabin4");
    set_deck(SHIP_DIR + "deck4");
    cap = clone_object(SHIP_DIR + "captain4");
    cap->arm_me();
    set_captain(cap);
    set_places_to_go(({THARBAD_DIR + "pier/pier1",
		       GWATHLO_DIR + "tharbad",
		       GWATHLO_DIR + "sriver1",
		       GWATHLO_DIR + "sriver2",
		       GWATHLO_DIR + "londdaer",
                       GWATHLO_DIR + "mouth",
                       BAY_DIR + "openwater",
                       BAY_DIR + "openwater2",
		       "/d/Krynn/solace/ship/sea3",
		       "/d/Krynn/solamn/splains/room/vriver1",
		       "/d/Ansalon/kalaman/room/dock2",
		       "/d/Krynn/solamn/splains/room/vriver1",
		       "/d/Krynn/solace/ship/sea3",
		       BAY_DIR + "openwater2",
		       BAY_DIR + "openwater",
		       GWATHLO_DIR + "mouth",
		       GWATHLO_DIR + "londdaer",
		       GWATHLO_DIR + "sriver2",
		       GWATHLO_DIR + "sriver1",
		       GWATHLO_DIR + "tharbad"}));
    set_time_between_stops(({20,
			     2,
			     2,
			     2,
			     2,
			     2,
                             2,
                             2,
                             2,
                             2,
                            20,
                             2,
                             2,
                             2,
                             2,
                             2,
                             2,
                             2,
                             2,
		 	     2}));
    set_ticket_id("the Tharbad-Kalaman line");
    set_name("ship");
    add_name("boat");
    add_adj("old");
    add_adj("corsair");
    set_long(BSN("This is an old corsair ship, rather run-down and in a"
               + " state of disrepair. Nevertheless, it looks like it"
               + " still has the ability to weather the open seas. A"
               + " dozen or so oars stick out from the sides of the"
               + " mighty hull, and a mighty grey sail is set above the"
               + " prow."));
    enable_reset();
}

void
reset_ship()
{
    object cap;
    if (!objectp(query_captain()))
    {
	cap = clone_object(SHIP_DIR + "captain4");
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
