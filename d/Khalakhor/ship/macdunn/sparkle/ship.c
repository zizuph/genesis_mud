/* File:          /d/Khalakhor/ship/macdunn/sparkle/ship.c
 * Creator:       Teth
 * Date:          April 13, 1997
 * Modifications: Converted from the Khalakhor/Ansalon run.
 *                Khail - November 27, 97.
 * Purpose:       This is the Macdunn-Sparkle, or Khalakhor-Sparkle
 *                ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/sparkle/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/ship";
#include "local.h"
#include <cmdparse.h>

public void
create_ship()
{
    object cap;    
    seteuid(getuid());
    set_deck(DECK);
    add_deck(DECK2);
    cap = clone_object(CAPTAIN);
    cap->arm_me();
    set_captain(cap);
    set_places_to_go(({
        MACDUNN_PIER,
        MACDUNN_DIR + "harbour",
        MACDUNN_DIR + "sea1",
        MACDUNN_DIR + "sea2",
        MACDUNN_DIR + "sea3",
        MACDUNN_DIR + "sea4",
        MACDUNN_DIR + "sea_sparkle",
        SPARKLE_PIER,
        MACDUNN_DIR + "sea_sparkle",
        MACDUNN_DIR + "sea4",
        MACDUNN_DIR + "sea3",
        MACDUNN_DIR + "sea2",
        MACDUNN_DIR + "sea1",
        MACDUNN_DIR + "harbour",
      }));

    set_time_between_stops(({
        20,
        3,
        5,
        2,
        3,
        6,
        2,
        20,
        2,
        6,
        3,
        2,
        5,
        3
      }));

    set_ticket_id(TICKET_NAME);
    set_name("longboat");
    add_name(SHIP_NAME);
    add_name("ship");
    add_name("boat");
    add_adj("sleek");
    add_adj("black");
    set_long("This sleek black ship is the Sgian Dubh, or " +
      "Black Knife, a ship running between the villages of " +
      "Port Macdunn and Sparkle. Three black, canvas sails " +
      "rise above her dark decks, her only apparent means " +
      "of motion. Built long and low, she looks not to be " +
      "built for heavy seas, but you doubt there are many " +
      "ships afloat that can outrun her.\n");
    add_item(({"sail","canvas sail"}),"The black sails " +
      "snap sharply in the wind, shining darkly in the " +
      "light.\n");
    add_item(({"deck","decks","dark decks"}),
      "The deck of the Sgian Dubh is made of the same " +
      "material as the rest of the ship, a solid wood, " +
      "probably oak, stained a dark black.\n");
}

public int
board(string what)
{
    object ticket, *tmp;

    if (!board_enabled)
    {
        return 0;
    }
    if (what && (!sizeof(tmp =
          FIND_STR_IN_OBJECT(what, environment(this_player()))) ||
        this_object() != tmp[0]))
    {
        return 0;
    }
    if (this_player()->query_average_stat() >= 20)
    {
        return ::board(what);
    }

    write("You board the ship.\n");
    environment(this_player())->set_dircmd(what);
    this_player()->move_living("boarding the ship", query_deck()[0]);
    return 1;
}


