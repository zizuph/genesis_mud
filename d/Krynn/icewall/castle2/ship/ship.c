inherit "/d/Genesis/ship/ship";
#include "local.h"
#include <cmdparse.h>

void
create_ship()
{
    object cap;
    seteuid(getuid());
    set_cabin(CABIN);
    add_cabin(CABIN2);
    set_deck(DECK);
    add_deck(DECK2);
    cap = clone_object(CAPTAIN);
    set_captain(cap);
    set_places_to_go(({
    ICE + "snow_plain11",
    TDIR + "sea4",
    TDIR + "sea3",
    TDIR + "sea2",
    TDIR + "sea1",
    PALANTHAS_ROOM,
        TDIR + "sea1",
        TDIR + "sea2",
        TDIR + "sea3",
        TDIR + "sea4",
    }));

    set_time_between_stops(({
        30,     /* Icewall */
            2,
            3,
            1,
            3,
            
            30, /* Palan */
            3,
            
            3,
            2,
            3,
            }));
    
    set_ticket_id(TICKET_NAME);
    set_name("schooner");
    add_name(SHIP_NAME);
    add_name("ship");
    add_adj("aged");
    add_adj("sturdy");
    set_long(break_string("This is a sturdy ocean-going schooner. " +
        "You see two masts on the vessels, and both forward as well as " +
        "aft rigging. The ship is old and blackened, but the hull " +
        "has been repeatedly reinforced. The rigging is also sturdier " +
        "then usual, designed not to crack under the weight of ice that " +
        "always builds up when one voyages in the icy seas of southern Krynn. " +
                 "\n", 70));

    add_prop(OBJ_I_WEIGHT, 34000000);
    add_prop(OBJ_I_VOLUME, 60000000);
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

    write("You board the schooner.\n");
    environment(this_player())->set_dircmd(what);
    this_player()->move_living("boarding the schooner", query_deck()[0]);
    return 1;
}


/* Description:   This function is here to give the players a warning
 *                before the ship leaves.
 *                as we leave almost sooner than we arrive, we won't
 *                give any warning at all.
 */
void
give_leave_warning()
{
}

