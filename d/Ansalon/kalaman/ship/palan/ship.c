inherit "/d/Genesis/ship/ship";
#include "local.h"
#include <cmdparse.h>

void
create_ship()
{
    object cap;    
    seteuid(getuid());
    set_cabin(CABIN);
    set_deck(DECK);
    cap = clone_object(CAPTAIN);
    set_captain(cap);
    set_places_to_go(({
	PIER2,
	ROOM + "sea1",
	ROOM + "sea2",
	ROOM + "sea4",
	ROOM + "sea5",
	/*... to and from Grey Havens ...*/
	SHIRE1,
	SHIRE3,
	GREY_HAVENS,
	SHIRE4,
	SHIRE3,
	SHIRE2,
	SHIRE1,
	/* */
	OPEN_SEA,
	ROOM + "sea1",
      }));

    set_time_between_stops(({
	23,
	2,
	2,
	2,
	2,
	/*to and from grey havens */
	2,
	2,
	24,
	2,
	2,
	2,
	2,
	/* */
	2,
	2,
	2
      }));

    set_ticket_id(TICKET_NAME);
    set_name("ship");
    add_name(SHIP_NAME);
    add_adj("hulking");
    add_adj("white");
    set_long(break_string("This great hulking ship is " +
	"made of a strange and exotic white wood, that allows " +
	"the vessel to sit lightly on the water. Looking at the " +
	"fore of the boat, you see it's name carved, 'Stumpy'.\n",70));
}


board(what)
{
    object ticket, *tmp;

    if (!board_enabled)
	return 0;
    if (what && (!sizeof(tmp =
	  FIND_STR_IN_OBJECT(what, environment(this_player()))) ||
	this_object() != tmp[0]))
	return 0;
    if (this_player()->query_average_stat() >= 20)
	return ::board(what);

    write("You board the ship.\n");
    environment(this_player())->set_dircmd(what);
    this_player()->move_living("boarding the ship", query_deck()[0]);
    return 1;
}

