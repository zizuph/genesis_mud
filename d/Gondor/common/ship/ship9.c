/* ship9.c

  Ship from Poros to island of Tolfalas
  Palmer 12 Aug 2006

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
    set_cabin(SHIP_DIR + "cabin9");
    set_deck(SHIP_DIR + "deck9");
    cap = clone_object(SHIP_DIR + "captain9");
    cap->arm_me();
    set_captain(cap);
    set_places_to_go(({POROS_DIR + "pier2",
                       BAY_DIR + "eshore2",
                       BAY_DIR + "openwater",
                       BAY_DIR + "openwater2",
                       BAY_DIR + "openwater3",
                       BAY_DIR + "openwater2",
                       BAY_DIR + "openwater3",
		       TOLFALAS_DIR + "room/pier",
                       BAY_DIR + "openwater3",
                       BAY_DIR + "openwater2",
                       BAY_DIR + "openwater3",
                       BAY_DIR + "openwater2",
                       BAY_DIR + "openwater",
                       BAY_DIR + "eshore2",
	 	               }));
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
    set_ticket_id("Poros Tolfalas line");
    set_name("ship");
    add_name("boat");
    add_adj("large");
    add_adj("sailing");
    set_long("Moored here is a large sailing ship, that currently " +
        "sails from the river Poros to the island of Tolfalas and back on a regular basis. "+
	"Due to the " +
        "fact that the captain has to make sure whether he will encounter " +
        "any pirates during the long trip, you never know when the ship " +
        "arrives and leaves. The boat itself made of dark wood and looks quite " +
       "new. There are various items, like ropes, lying here.\n");
   enable_reset();
}

void
reset_ship()
{
    object cap;
    if (!objectp(query_captain()))
    { 
	cap = clone_object(SHIP_DIR + "captain9");
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
