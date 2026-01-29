/**********************************************************************
 * - ship.c                                                         - *
 * -                                                                - *
 * - Created by Damaris@Genesis 02/2001                             - *
 * - Updated by Damaris@Genesis 03/2005                             - *
 **********************************************************************/

#pragma save_binary
#pragma strict_types
 
inherit "/d/Genesis/ship/ship";
#include "local.h"
#include <cmdparse.h>
#define  TP (this_player())
 
public void
create_ship()
{
	object cap;
	seteuid(getuid());
        set_cabin(CABIN);
        set_deck(DECK);
        cap = clone_object(CAPTAIN);
        cap->arm_me();
        set_captain(cap);
        set_places_to_go(({
		MACDUNN_DIR + "pier14",
                MACDUNN_DIR + "harbour",
                MACDUNN_DIR + "sea1",
                MACDUNN_DIR + "sea2",
                MACDUNN_DIR + "sea3",
                MACDUNN_DIR + "sea4",
                MACDUNN_DIR + "sea_samorgan",
                SAMORGAN_PIER,
                MACDUNN_DIR + "sea_samorgan",
                MACDUNN_DIR + "sea4",
                MACDUNN_DIR + "sea3",
                MACDUNN_DIR + "sea2",
                MACDUNN_DIR + "sea1",
                MACDUNN_DIR + "harbour",
                }));
                
                set_time_between_stops
                (({
			20, 3, 5, 2, 3, 6, 2,
			20, 2, 6, 3, 2, 5, 3
		}));
	set_ticket_id(TICKET_NAME);
	set_name("boat");
	add_name(SHIP_NAME);
	add_name("ship");
	add_adj(({"sturdy","wooden"}));
	set_short("sturdy wooden ship");
	set_long("This sturdy wooden ship is named the "+SHIP_NAME+
        "and is famed for its great luck in sailing the south seas of "+
        "Khalakhor. The ship travels the route between Port MacDunn " +
        "and the village of SaMorgan.\n");
        add_item("mast",
        "The central mast of the ship is massive. You wonder how "+
        "the ship doesn't topple over from its weight. Obviously "+
        "designed to withstand powerful winds, it rises high above "+
        "the deck laden with large sails.\n");
        add_item("sails",
        "The large white sails hanging from the mast seem to be made of "+
        "wool and are very voluminous. You imagine a heavy wind in "+
        "those sails on that mast could carry the ship very quickly "+
        "and safely.\n");
}
 
public int board(string what)
{
	object ticket, *tmp;
	if (!board_enabled) return 0;
	if (what && (!sizeof(tmp = FIND_STR_IN_OBJECT(what, environment(TP))) || this_object() != tmp[0]))
	return 0;
	if (this_player()->query_average_stat() >= 20) return ::board(what);
	write("You board the ship.\n");
	environment(TP)->set_dircmd(what);
	TP->move_living("boarding the ship", query_deck()[0]);
	return 1;
}
