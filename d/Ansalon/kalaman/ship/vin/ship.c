#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/ship";
#include "local.h"
#include <cmdparse.h>
#include <stdproperties.h>

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
	"/d/Ansalon/kalaman/room/dock5",
	ROOM + "sea1",
	ROOM + "sea2",
	ROOM + "sea3",
	ROOM + "sea4",
	ROOM + "sea5",
	GREY_HAVENS,
	ROOM + "sea5",
	ROOM + "sea4",
	ROOM + "sea3",
	ROOM + "sea2",
	ROOM + "sea1",
      }));


    set_time_between_stops(({
	23,
	2,
	2,
	2,
	2,
	2,
	24,
	2,
	2,
	2,
	2,
	2
      }));

    set_ticket_id(TICKET_NAME);
    set_name("boat");
    add_name("ship");
    add_name(SHIP_NAME);
    add_adj("long");
    add_adj("river");
    set_long("This long river boat travels the down " +
      "the Vingaard River, carrying cargo and passengers " +
      "from Kalaman to the Vingaard Keep.\n");
    add_prop(OBJ_I_VOLUME, 6000);
}

int
board(mixed what)
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

