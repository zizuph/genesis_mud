/*
 * Ship between Faerun and Flotsam
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
    set_cabin(FLOTSAM_DIR + "cabin");
    set_deck(FLOTSAM_DIR + "deck");
    cap = clone_object(FLOTSAM_DIR + "captain");
    cap->arm_me();
    set_captain(cap);

    set_places_to_go(({FAERUN_PIER_DIR + "beach03",
               FLOTSAM_DIR + "openwater1",
               FLOTSAM_DIR + "openwater2",
               FLOTSAM_DIR + "openwater3",
               FLOTSAM_DIR + "openwater4",
               FLOTSAM_DIR + "openwater5",
               FLOTSAM_DIR + "openwater6",
               FLOTSAM_DIR + "openwater7",
    FLOTSAM_PIER,
                FLOTSAM_DIR + "openwater7",
                FLOTSAM_DIR + "openwater6",
                FLOTSAM_DIR + "openwater5",
                FLOTSAM_DIR + "openwater4",
                FLOTSAM_DIR + "openwater3",
                FLOTSAM_DIR + "openwater2",
                FLOTSAM_DIR + "openwater1",}));


 
    set_time_between_stops(({24, 3, 3, 3, 3, 3, 3, 3,
                             24, 3, 3, 3, 3, 3, 3, 3}));

    set_ticket_id(FLOTSAM_TICKET_NAME);
    set_name("caravel");
    add_name("ship");
    add_name("boat");
    add_adj("slim");
    add_adj("fast");
    set_short("slim fast caravel");
    set_long("This is a wooden ship known as the 'Sea Lion'. It is small and highly maneuverable on the open seas. The ship has two masts with two large triangular sails. The deck is scrubbed clean. It is well maintained and sails between Flotsam and Faerun.\n");
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
    cap = clone_object(FLOTSAM_DIR + "captain");
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
