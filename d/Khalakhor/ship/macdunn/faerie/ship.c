/* File:          /d/Khalakhor/ship/macdunn/faerie/ship.c
 * Creator:       Teth
 * Date:          November 13, 1997
 * Modifications:
 * Purpose:       This is the Macdunn-Faerie, or Khalakhor-Faerie
 *                ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/faerie/
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
    set_cabin(CABIN);
    set_deck(DECK);
    cap = clone_object(CAPTAIN);
    cap->arm_me();
    set_captain(cap);
    set_places_to_go(({
        MACDUNN_DIR + "pier10",
        MACDUNN_DIR + "harbour",
        MACDUNN_DIR + "sea1",
        MACDUNN_DIR + "sea2",
        MACDUNN_DIR + "sea3",
        MACDUNN_DIR + "sea4",
        MACDUNN_DIR + "sea_faerie",
        FAERIE_PIER,
        MACDUNN_DIR + "sea_faerie",
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
    set_name("boat");
    add_name(SHIP_NAME);
    add_name("ship");
    add_adj(({"elegant","sailed","silk-sailed"}));
    set_short("elegant silk-sailed boat");
    set_long("This elegant boat is named the Fiu Alladh, " +
      "and is famed for its light-weight construction and its " +
      "silk sails. The boat travels the route between Port " +
      "Macdunn and the land of Faerie. Despite appearances, " +
      "the boat seems sturdy enough for many future voyages.\n");
    add_item(({"construction","structure",
        "light-weight construction","light-weight structure"}),
      "The apparent light-weight structure of the boat seems to " +
      "be deceptive on second glance.\n");
    add_item(({"sails","sail","silk sails","silk sail"}),
      "Finely woven, the sails catch the wind like the taut wing " +
      "of a searching bird of prey.\n");
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

