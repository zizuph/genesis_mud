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

#define GH_DIR "/d/Shire/common/ship/"

void
create_ship()
{
    object cap;    

    seteuid(getuid());

    set_cabin(SHIP_DIR + "cabin8");
    set_deck(SHIP_DIR + "deck8");
    cap = clone_object(SHIP_DIR + "captain8");
    cap->arm_me();
    set_captain(cap);
    set_places_to_go(({ANDUIN_DIR + "harlond/pier3",
		        ANDUIN_DIR + "pelargir",
		        ANDUIN_DIR + "sriver3",
		        ANDUIN_DIR + "sriver1",
		        ANDUIN_DIR + "harlond",
                ANDUIN_DIR + "gh1",
                ANDUIN_DIR + "gh2",
                ANDUIN_DIR + "gh3",
                ANDUIN_DIR + "gh4",
                ANDUIN_DIR + "gh5",
                ANDUIN_DIR + "gh6",
                ANDUIN_DIR + "gh7",
                ANDUIN_DIR + "gh8",
                GH_DIR     + "w6",
                GH_DIR     + "mt1",               
                       GH_DIR + "pier8",
                GH_DIR     + "mt1",
                GH_DIR     + "w6",
                ANDUIN_DIR + "gh8",
                ANDUIN_DIR + "gh7",
                ANDUIN_DIR + "gh6",
                ANDUIN_DIR + "gh5",
                ANDUIN_DIR + "gh4",
                ANDUIN_DIR + "gh3",
                ANDUIN_DIR + "gh2",
                ANDUIN_DIR + "gh1",
		        ANDUIN_DIR + "harlond",
		        ANDUIN_DIR + "sriver1",
		        ANDUIN_DIR + "sriver3",
		        ANDUIN_DIR + "pelargir", }));
    set_time_between_stops(({45,
                              3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 3, 3,
                             45,
                              3, 3, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, }));


    set_ticket_id("The Harlond to Mithlond Line");
    set_name("ship");
    add_name("boat");
    set_adj(({"large", "sea-worthy"}));
    set_long("This is a large sea-worthy ship. It is built to withstand " +
        "the ocean and often sails on the Great Sea. Its hull is pointed " +
        "and enables the ship to cut across the water efficiently. It " +
        "is powered by large sails on three masts and oars.");
    enable_reset();
}

void
reset_ship()
{
    object cap;
    if (!objectp(query_captain()))
    {
        cap = clone_object(SHIP_DIR + "captain8");
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
