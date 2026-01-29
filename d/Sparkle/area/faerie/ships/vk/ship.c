/*
 * Ship between Faerie and VK
 * Modified from Pelargir ship in Gondor
 * -- Finwe, 2006
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/ship";
#include <cmdparse.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

void
create_ship()
{
    object cap;    
    seteuid(getuid());
    set_cabin(VK_SHIP_DIR + "cabin");
    set_deck(VK_SHIP_DIR + "deck");
    cap = clone_object(VK_SHIP_DIR + "captain");
    cap->arm_me();
    set_captain(cap);

    set_places_to_go(({FOREST_DIR + "pier01n",
               VK_SHIP_DIR + "openwater1",
               VK_SHIP_DIR + "openwater2",
               VK_SHIP_DIR + "openwater3",
               VK_SHIP_DIR + "openwater4",
               VK_SHIP_DIR + "openwater5",
               VK_SHIP_DIR + "openwater6",
               VK_SHIP_DIR + "openwater7",
    "/d/Krynn/solamn/splains/room/pier1",
                VK_SHIP_DIR + "openwater7",
                VK_SHIP_DIR + "openwater6",
                VK_SHIP_DIR + "openwater5",
                VK_SHIP_DIR + "openwater4",
                VK_SHIP_DIR + "openwater3",
                VK_SHIP_DIR + "openwater2",
                VK_SHIP_DIR + "openwater1",}));


 
    set_time_between_stops(({24, 3, 3, 3, 3, 3, 3, 3,
                             24, 3, 3, 3, 3, 3, 3, 3}));

    set_ticket_id("_faerie_vk_ticket_");
    set_name("ship");
    add_name("boat");
    add_adj("large");
    add_adj("sailing");
    set_long("This is a large sailing ship. It sails between Faerie and " +
        "Vingaard Keep. It looks like it's a fast vessel and in good " +
        "condition. Because it sails on the open sea, its arrival time " +
        "may be sporadic.\n");
   enable_reset();

// prevents dmage from draco acids
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
    cap = clone_object(VK_SHIP_DIR + "captain");
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
