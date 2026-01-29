inherit "/d/Genesis/ship/ship";
#include <cmdparse.h>
#include "local.h"

private void
load_priv(string ob)
{
    (ob)->load_me();
    (ob)->set_no_disembark();
}

void
create_ship()
{
    object cap;    
    seteuid(getuid());

    set_deck(DECK2);

    set_alarm(0.0, 0.0, &add_deck(DECK3));
    set_alarm(0.0, 0.0, &load_priv(DECK3));
    set_alarm(0.0, 0.0, &add_deck(DECK4));
    set_alarm(0.0, 0.0, &load_priv(DECK4));
    set_alarm(0.0, 0.0, &add_deck(DECK5));
    set_alarm(0.0, 0.0, &load_priv(DECK5));
    set_alarm(0.0, 0.0, &add_deck(DECK6));
    set_alarm(0.0, 0.0, &load_priv(DECK6));
    set_alarm(0.0, 0.0, &add_deck(DECK7));
    set_alarm(0.0, 0.0, &load_priv(DECK7));
    set_alarm(0.0, 0.0, &add_deck(DECK8));
    set_alarm(0.0, 0.0, &load_priv(DECK8));
    set_alarm(0.0, 0.0, &add_deck(DECK9));
    set_alarm(0.0, 0.0, &load_priv(DECK9));
    set_alarm(0.0, 0.0, &add_deck(DECK10));
    set_alarm(0.0, 0.0, &load_priv(DECK10));
    set_alarm(0.0, 0.0, &add_deck(DECK11));
    set_alarm(0.0, 0.0, &load_priv(DECK11));
    set_alarm(0.0, 0.0, &add_deck(DECK12));
    set_alarm(0.0, 0.0, &load_priv(DECK12));
    set_alarm(0.0, 0.0, &add_deck(DECK13));
    set_alarm(0.0, 0.0, &load_priv(DECK13));

    set_cabin(CABIN1);
    set_alarm(0.0, 0.0, &load_priv(CABIN1));
    set_alarm(0.0, 0.0, &add_cabin(CABIN2));
    set_alarm(0.0, 0.0, &load_priv(CABIN2));
    set_alarm(0.0, 0.0, &add_cabin(CABIN3));
    set_alarm(0.0, 0.0, &load_priv(CABIN3));
    set_alarm(0.0, 0.0, &add_cabin(CABIN4));
    set_alarm(0.0, 0.0, &load_priv(CABIN4));
    set_alarm(0.0, 0.0, &add_cabin(CABIN5));
    set_alarm(0.0, 0.0, &load_priv(CABIN5));

    cap = clone_object(CAPTAIN);
    set_captain(cap);
    set_places_to_go(({
	PIER1,
	ROOM + "sea1",
	ROOM + "sea2",
	ROOM + "sea3",
	ROOM + "sea4",
	ROOM + "sea5",
	ROOM + "sea6",
	ROOM + "sea7",
	ROOM + "sea8",
	ROOM + "sea9",
	SPARCLE_10,
	ROOM + "sea9",
	ROOM + "sea8",
	ROOM + "sea7",
	ROOM + "sea6",
	ROOM + "sea5",
	ROOM + "sea4",
	ROOM + "sea3",
	ROOM + "sea2",
	ROOM + "sea1",
      }));

    set_time_between_stops(({
	23,
	2,2,2,2,2,2,2,2,2,
	24,
	2,2,2,2,2,2,2,2,2
      }));

    set_ticket_id(TICKET_NAME);
    set_name("ship");
    add_name(SHIP_NAME);
    add_adj("sleek");
    add_adj("pirate");
    set_long("This sleek sailing ship in outfitted " +
	"with two masts with large square sails. Apart from a " +
	"few ballistas stationed on both fore and aft of the ship " +
	"this seems to be nothing more than a fast merchant ship. " +
	"Still, it wouldn't surprise you to find that this ship " +
	"has been used in pirate raids along the coastline.\n");
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

