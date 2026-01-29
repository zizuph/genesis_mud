/*********************************************************************
 * - ship.c                                                        - *
 * - shipline Gont-Kabal                                           - *
 * - Recoded by Damaris 5/2003                                     - *
 *********************************************************************/
 
#pragma save_binary
#pragma strict_types
 
inherit "/d/Genesis/ship/ship";
#include "../default.h"
#include "defs.h"
#include <cmdparse.h>
 
public void
create_ship()
{
    object cap;
    seteuid(getuid());
    set_cabin(CABIN);
    set_deck(DECK);
    cap = clone_object(CAPTAIN);
    set_captain(cap);
   set_places_to_go(({PORT + "shipline/pier",
	PORT + "shipline/sea",
	PORT + "shipline/sea1",
	PORT + "shipline/sea2",
	PORT + "shipline/sea3",
	PORT + "shipline/sea4",
	"/d/Earthsea/gont/gont_city/rooms/north_pier1",
	PORT + "shipline/sea4",
	PORT + "shipline/sea3",
	PORT + "shipline/sea2",
	PORT + "shipline/sea1",
	PORT + "shipline/sea"}));
    set_time_between_stops
      (({
        24, 4, 4, 4, 4, 4,
	24, 4, 4, 4, 4,	4
      }));
 
    set_ticket_id(TICKET_NAME);
    set_name("boat");
    add_name(SHIP_NAME);
    add_name("ship");
    add_adj(({"enormous","wooden"}));
    set_short("enormous wooden ship");
    set_long("This enormous wooden ship is named the "+SHIP_NAME+ " "+
       "and by it's size it must be a galleon.\n");
    add_item("mast",
       "The central mast of the ship is massive. You wonder how "+
       "the ship doesn't topple over from its weight. Obviously designed "+
       "to with stand powerful winds, it rises high above the deck "+
       "laden with large sails.\n");
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
 
    if (what && (!sizeof(tmp = FIND_STR_IN_OBJECT(what, environment(TP))) ||
        this_object() != tmp[0]))
        return 0;
 
    if (this_player()->query_average_stat() >= 20) return ::board(what);
 
    write("You board the ship.\n");
    environment(TP)->set_dircmd(what);
    TP->move_living("boarding the ship", query_deck()[0]);
    return 1;
}
