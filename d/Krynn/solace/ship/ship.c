inherit "/d/Genesis/ship/ship";
#include "local.h"
#include <cmdparse.h>

void
create_ship()
{
    object cap;    
    seteuid(getuid());
    set_deck(DECK);
    cap = clone_object(CAPTAIN);
    set_captain(cap);
    set_places_to_go(({
    TDIR + "pier",
    TDIR + "lake1",
    TDIR + "lake2",
    TDIR + "stream1",
    TDIR + "stream2",
    TDIR + "river1",
    TDIR + "bay1",
    DESTIN_ROOM,
    TDIR + "bay1",
    TDIR + "river1",
    TDIR + "stream2",
    TDIR + "stream1",
    TDIR + "lake2",
    TDIR + "lake1",
    }));

    set_time_between_stops(({
	24,
	1,
        1,
        1,
	1,
	1,
        1,
        24,
        1,
	1,
	1,
        1,
        1,
        1
    }));

    set_ticket_id(TICKET_NAME);
    set_name("rowboat");
    add_name("ship");
    add_name(SHIP_NAME);
    add_adj("small");
    add_adj("sturdy");
    set_long(break_string("This is a small sturdy rowboat. " +
        "It is owned by a local villager, who uses it to " +
        "transport people between Solace and Newports, along " +
        "Crystalmir Lake, Solace Stream, WhiteRage River and " +
        "the Newsea.\n", 70));
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

    write("You board the rowboat.\n");
    environment(this_player())->set_dircmd(what);
    this_player()->move_living("boarding the rowboat", query_deck()[0]);
    return 1;
}

