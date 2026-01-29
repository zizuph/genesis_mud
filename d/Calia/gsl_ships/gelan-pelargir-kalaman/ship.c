#pragma save_binary

inherit "/d/Genesis/ship/ship";
#include <stdproperties.h>
#include "ship.h"
#include "/sys/cmdparse.h"

void
create_ship()
{
	object cap;
    
        setuid();
	seteuid(getuid());
	set_deck(SHIPS+"deck");
	set_cabin(SHIPS+"cabin.c");
	cap = clone_object(SHIPS+"captain.c");
	set_captain(cap);
	set_places_to_go(({
		GELAN_PORT,
		WATER1,
		WATER2,
		WATER3,
		WATER4,
                WATER5,
		KRYNN_PORT,
                WATER5,
		WATER4,
		WATER3,
		WATER2,
		WATER1}));
	set_time_between_stops(({
		24,
		4,
		4,
		4,
		4,
                4,
		24,
		4,
		4,
		4,
		4,
                4}));
	set_ticket_id("gelan-palanthas line");
	set_board_enabled(1);
	set_name("ship");
	add_name("boat");
	add_adj("walnut");
	add_adj("floating");
        set_short("floating walnut ship");
        set_long("This ship, which is half as wide as it is long, is " +
                "made of knotted wood that has been painted beige. " +
                "This gives it the appearance of an upturned walnut " +
                "half-shell. Silly, isn't it?\n");
}


int
board(string what)
{
	object ticket, *tmp;

	if (!board_enabled)
		return 0;
	if (what && (!sizeof(tmp =
		FIND_STR_IN_OBJECT(
			what,E(TP))) || TO != tmp[0]))
		return 0;
	if (TP->query_average_stat() >=20)
		return::board(what);
	write("You board the ship.\n");
	E(TP)->set_dircmd(what);
	TP->move_living("boarding the ship", query_deck()[0]);
	return 1;
}