/*
 *  A ship to run from the Fords of Poros to Pelargir upon Anduin,
 *  Tharbad upon Gwathlo, and back
 *
 *  Olorin, June 1995
 *
 *  Modified:
 *  Oct 1997 by Fysix: adjusted board function for steeds.
 *                     Prevent steeds from boarding this ship.
 *  Oct 2002 by Gwyneth: Removed prevention of steeds on this ship.
 */
#pragma save_binary
#pragma strict_types
#include "/d/Gondor/defs.h"
inherit "/d/Genesis/ship/ship";
//inherit STD_DIR + "steed/prevent_steed";
#include <cmdparse.h>

void
create_ship()
{
    object cap;    
    seteuid(getuid());
    set_cabin(SHIP_DIR + "cabin6");
    set_deck(SHIP_DIR + "deck6");
    cap = clone_object(SHIP_DIR + "captain6");
    cap->arm_me();
    set_captain(cap);
    set_places_to_go(({ITH_DIR + "poros/pier",
		       ITH_DIR + "poros/river1",
		       ITH_DIR + "poros/river2",
                       ANDUIN_DIR + "mouth",
                       LEB_DIR + "sroad/south_pier",
                       ANDUIN_DIR + "mouth",
                       BAY_DIR + "eshore2",
                       BAY_DIR + "openwater",
                       GWATHLO_DIR + "mouth",
		       GWATHLO_DIR + "londdaer",
		       GWATHLO_DIR + "sriver2",
		       GWATHLO_DIR + "sriver1",
		       GWATHLO_DIR + "tharbad",
		       THARBAD_DIR + "pier/pier4",
		       GWATHLO_DIR + "tharbad",
		       GWATHLO_DIR + "sriver1",
		       GWATHLO_DIR + "sriver2",
		       GWATHLO_DIR + "londdaer",
                       GWATHLO_DIR + "mouth",
                       BAY_DIR + "openwater",
                       BAY_DIR + "eshore2",
                       ANDUIN_DIR + "mouth",
                       LEB_DIR + "sroad/south_pier",
                       ANDUIN_DIR + "mouth",
		       POROS_DIR + "river2",
		       POROS_DIR + "river1", }));
    set_time_between_stops(({	24,
				 3,
				 3,
				 3,
				20,
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
				 3,
				20,
				 3,
				 3,
				 3,
				}));
    set_ticket_id("Poros-Tharbad Corsair Line");
    set_name("corsair");
    set_short("small corsair");
    add_name(({"herifalmar", "ship", "boat", "vessel", }));
    add_adj(({"small", "run-down", }));
    set_long("This is a small sailing ship with a single mast with "
      + "a low keel so it can be used to sail up rivers. The ship is "
      + "rather old and a little shabby, but it does look to be in "
      + "good repair. The name 'Herifalmar' has been painted onto the bow.\n");
    enable_reset();
    
    // Added by Fysix: don't allow steeds on this ship
    //set_no_allow_steed(1);
}

void
reset_ship()
{
    object cap;
    if (!objectp(query_captain()))
    {
        cap = clone_object(SHIP_DIR + "captain6");
	cap->arm_me();
        set_captain(cap);
        cap->move(query_deck()[0]);
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
