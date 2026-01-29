/*
 * Ship between Faerie and Shire
 * Modified from Pelargir ship in Gondor
 * -- Finwe, 2006
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/ship.c";

#include <cmdparse.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#include "defs.h"
#include "/d/Faerun/defs.h"

void
create_ship()
{
    object cap;    
    seteuid(getuid());
    set_cabin(SHIRE_DIR + "cabin");
    set_deck(SHIRE_DIR + "deck");
    cap = clone_object(SHIRE_DIR + "captain");
    cap->arm_me();
    set_captain(cap);

    set_places_to_go(({FAERUN_PIER_DIR + "beach04",
               SHIRE_DIR + "openwater1",
               SHIRE_DIR + "openwater2",
               SHIRE_DIR + "openwater3",
               SHIRE_DIR + "openwater4",
               SHIRE_DIR + "openwater5",
               SHIRE_DIR + "openwater6",
               SHIRE_DIR + "openwater7",
    SHIRE_PIER,
                SHIRE_DIR + "openwater7",
                SHIRE_DIR + "openwater6",
                SHIRE_DIR + "openwater5",
                SHIRE_DIR + "openwater4",
                SHIRE_DIR + "openwater3",
                SHIRE_DIR + "openwater2",
                SHIRE_DIR + "openwater1",}));


 
    set_time_between_stops(({24, 3, 3, 3, 3, 3, 3, 3,
                             24, 3, 3, 3, 3, 3, 3, 3}));

    set_ticket_id(SHIRE_TICKET_NAME);
    set_name("vessel");
    add_name("ship");
    add_name("boat");
    add_adj("fast");
    add_adj("wooden");
    set_short("fast wooden ship");
    set_long("This is a wooden ship. It sails the open sea between Faerun and the Shire. The boat looks well maintained but very common looking. It looks to be a common ship that sails along the Sword Coast. Because it sails on the open sea, its arrival time may be sporadic.\n");
   enable_reset();

// prevents damage from draco acids
    add_prop(OBJ_I_RES_ACID, 200);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }));

}

void
reset_ship()
{
    object cap;
    if (!objectp(query_captain()))
    { 
    cap = clone_object(SHIRE_DIR + "captain");
    cap->arm_me();
    set_captain(cap);
    cap->move(query_deck()[0]);
    sail_away_out_on_the_open_sea();
    }
}

int
board(string what)
{
    object ticket, *tmp;
    
    if (!board_enabled)
    return 0;
    if (what && (!sizeof(tmp =
                FIND_STR_IN_OBJECT(what, ENV(TP))) ||
               TO != tmp[0]))
    return 0;
    if (TP->query_average_stat() >= 20)
    return ::board(what);

    // Added a check to see if player can board, Fysix, October 1997
    if (!query_cannot_board_ship(TP, query_deck()[0]))
    {
        write("You board the ship.\n");
        ENV(TP)->set_dircmd(what);
        TP->move_living("boarding the ship", query_deck()[0]);
    }
    return 1;
}
