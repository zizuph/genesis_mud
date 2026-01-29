/* Navarre June 11th 2006, added name ship to the ship */

inherit "/d/Genesis/ship/ship";
#include "local.h"
#include <cmdparse.h>

int stop_next = 0;

void
create_ship()
{
    object cap;

    seteuid(getuid());
    set_deck(DECK);
    cap = clone_object(CAPTAIN);
    set_captain(cap);

    set_places_to_go(({ PIER_EAST,
			    RIVER1,
			    RIVER2,
			    RIVER3,
			    PIER_WEST,
			    RIVER3,
			    RIVER2,
			    RIVER1,
			    }));

    set_time_between_stops(({	15,
				7,
				5,
				7,
				15,
				7,
				7,
				5
				}));

    set_ticket_id(TICKET_NAME);
    set_name("ferry");
    add_name("ship");
    add_name(SHIP_NAME);
    add_adj("small");
    add_adj("creaking");
    set_long("This is a small creaking ferry used for transport across the " +
	     "Vingaard River during a flood.\n");
    add_prop(OBJ_I_VOLUME, 6000);
	    
}

int
board(string what)
{
    object ticket, *tmp;
    string occupant, tp_army;
    int oc_align, tp_align;

    if (!board_enabled)
	return 0;
    if (what &&
	(!sizeof(tmp = FIND_STR_IN_OBJECT(what, environment(this_player()))) ||
	 this_object() != tmp[0]))
	return 0;

    occupant = ARMYMASTER->army_in_area(WAR_AREA_GUARDLUND);
    oc_align = ARMYMASTER->army_alignment(occupant);
    tp_army = ARMYMASTER->army_of_player(this_player());
    tp_align = ARMYMASTER->army_alignment(tp_army);
    if (!ARMYMASTER->query_peace() && occupant != "Free People" &&
	((oc_align < 0 && tp_align >= 0) || (oc_align > 0 && tp_align < 0)))
    {
	notify_fail("The ferryman says: Current authorities do not allow you to board.\n");
	return 0;
    }

    if (this_player()->query_average_stat() >= 20)
 	return ::board(what);

    write("You board the ship.\n");
    environment(this_player())->set_dircmd(what);
    this_player()->move_living("boarding the ship", query_deck()[0]);
    return 1;
}

void
stop_at_next_possibility()
{
    /* well, not exactly next possibility, but rather immediately ;-) */
    stop_ship("The ferry suddenly crashes hard on something solid due " +
	      "to the rapidly retreating water. You are thrown onto " +
	      "the ground next to the ferry.\n");
    all_inventory(query_deck())->move(places_to_go[location],1);
    query_captain()->go_home();
    set_alarm(0.1,0.0,remove_object);
}
