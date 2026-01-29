inherit "/d/Genesis/ship/ship";
#include "local.h"
#include <cmdparse.h>

int da_boarding = 0;

void
reset_da_boarding()
{
    da_boarding = 0;
}

void
create_ship()
{
    object cap;
    seteuid(getuid());
    set_cabin(CABIN);
    set_deck(DECK);
    add_deck(UPPER);
    cap = clone_object(CAPTAIN);
    set_captain(cap);
    set_callout_fq(2);
    set_places_to_go(({
    PIER,
    ROOM + "sea1",
    ROOM + "sea2",
    ROOM + "sea3",
    ROOM + "sea4",
    ROOM + "sea5",
    ROOM + "sea6",
    ROOM + "sea7",
    ROOM + "sea8",
    ROOM + "sea9",
    ROOM + "sea10",
    ROOM + "sea11",
    ROOM + "sea12",
    ROOM + "sea13",

    PIER2,
    ROOM + "sea13",
    ROOM + "sea12",
    ROOM + "sea11",
    ROOM + "sea10",
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
    14,
    1,
    2,
    3,
    2,
    4,
    3,
    2,
    3,
    5,
    2,
    5,
    3,
    2,
    14,
    1,
    2,
    3,
    2,
    4,
    3,
    2,
    3,
    5,
    2,
    5,
    3,
    2,
      }));

    set_ticket_id(TICKET_NAME);
    set_name("ship");
    add_name(SHIP_NAME);
    add_adj("sleek");
    add_adj("dragonarmy");
    set_long("This sleek ship is decorated with marks of the Dragonarmies. " +
        "It is probably used as a fast courier ship, judging from the " +
        "size of it.\n");
}


board(what)
{
    object ticket, *tmp;
    mixed team;
    int i;

    if (!board_enabled)
    return 0;
    if (what &&
	(!sizeof(tmp = 	FIND_STR_IN_OBJECT(what, environment(this_player()))) ||
	 this_object() != tmp[0]))
	return 0;

    if (this_player()->query_dragonarmy_occ_member())
    {
	da_boarding = 1;
	set_alarm(0.0, 0.0, reset_da_boarding);
    }
    else
    {
	team = this_player()->query_team_others();
	for (i = 0; i < sizeof(team); i++)
	    if (team[i]->query_dragonarmy_occ_member())
	    {
		da_boarding = 1;
		set_alarm(0.0, 0.0, reset_da_boarding);
		break;
	    }
    }

    if (this_player()->query_average_stat() >= 20)
	return ::board(what);

    write("You board the ship.\n");
    environment(this_player())->set_dircmd(what);
    this_player()->move_living("boarding the ship", query_deck()[0]);
    return 1;
}

/*
 * Function name: query_deck
 * Description	: We want DA members and teammates to board directly to upper deck
 */
public mixed
query_deck()
{
    if (da_boarding)
	return ({ UPPER });
    return ::query_deck();
}

