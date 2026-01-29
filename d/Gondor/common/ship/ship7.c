/*
 *	/d/Gondor/common/ship/ship7.c
 *
 *	The ship running between Pelargir and Minas Tirith
 *
 *  Modified:
 *  Oct 1997 by Fysix: adjusted board function for steeds.
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

    set_cabin(SHIP_DIR + "cabin7");
    set_deck(SHIP_DIR + "deck7");
    cap = clone_object(SHIP_DIR + "captain7");
    cap->arm_me();
    set_captain(cap);
    set_places_to_go(({PELAR_DIR + "docks/dock2",
		       ANDUIN_DIR + "pelargir",
		       ANDUIN_DIR + "sriver4",
		       ANDUIN_DIR + "sriver3",
		       ANDUIN_DIR + "sriver2",
		       ANDUIN_DIR + "sriver1",
		       ANDUIN_DIR + "harlond",
                       MINAS_DIR + "harlond/pier1",
		       ANDUIN_DIR + "harlond",
		       ANDUIN_DIR + "sriver1",
		       ANDUIN_DIR + "sriver2",
		       ANDUIN_DIR + "sriver3",
		       ANDUIN_DIR + "sriver4",
		       ANDUIN_DIR + "pelargir", }));
    set_time_between_stops(({24,
                              4,
                              4,
                              4,
                              4,
                              4,
                              4,
                             24,
                              2,
                              2,
                              2,
                              2,
                              2,
                              2, }));
    set_ticket_id("The Pelargir - Harlond River-line");
    set_name("boat");
    add_name("ship");
    set_adj(({"large", "river"}));
    set_long("This is a large river boat, built for traffic on the "
      + "Anduin. Its wide hull makes it a slow but safe means of "
      + "transportation. It is powered by oars and a large grey sail "
      + "on a single mast. On top of the sail, the banner of Pelargir "
      + "is flown. Written onto the bow is the name \"Anduilunte\".");
    enable_reset();
}

void
reset_ship()
{
    object cap;
    if (!objectp(query_captain()))
    {
        cap = clone_object(SHIP_DIR + "captain7");
	cap->arm_me();
        set_captain(cap);
        cap->move(query_deck()[0]);
        start_ship(location);
    }
}

int
board(string what)
{
    object ticket, *tmp;

    if (!board_enabled)
        return 0;
    if (what && (!sizeof(tmp =
        FIND_STR_IN_OBJECT(what, environment(TP))) ||
        TO != tmp[0]))
        return 0;
    if (TP->query_average_stat() >= 20)
        return ::board(what);

    // Added a check to see if player can board, Fysix, October 1997
    if (!query_cannot_board_ship(TP, query_deck()[0]))
    {
        write("You board the ship.\n");
        environment(TP)->set_dircmd(what);
        TP->move_living("boarding the ship", query_deck()[0]);
    }

    return 1;
}
