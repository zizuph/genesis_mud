/* File:          /d/Khalakhor/ship/macdunn/shire/ship.c
 * Creator:       Teth
 * Date:          December 2, 1997
 * Modifications:
 * Purpose:       This is the Macdunn-Grey Havens, or Khalakhor-Shire
 *                ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/shire/
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
    add_cabin(CABIN2);
    set_deck(DECK);
    add_deck(DECK2);
    cap = clone_object(CAPTAIN);
    cap->arm_me();
    set_captain(cap);
    set_places_to_go(({
        MACDUNN_DIR + "pier12",
        MACDUNN_DIR + "harbour",
        MACDUNN_DIR + "sea1",
        MACDUNN_DIR + "sea2",
        MACDUNN_DIR + "sea3",
        MACDUNN_DIR + "sea4",
        MACDUNN_DIR + "sea_greyhavens",
        GREYHAVENS_PIER,
        MACDUNN_DIR + "sea_greyhavens",
        MACDUNN_DIR + "sea4",
        MACDUNN_DIR + "sea3",
        MACDUNN_DIR + "sea2",
        MACDUNN_DIR + "sea1",
        MACDUNN_DIR + "harbour",
      }));

    set_time_between_stops(({
        20,
        2,
        3,
        2,
        3,
        4,
        2,
        20,
        2,
        4,
        3,
        2,
        3,
        2
      }));

    set_ticket_id(TICKET_NAME);
    set_name("ship");
    add_name(SHIP_NAME);
    add_name("boat");
    add_name("vessel");
    add_adj("sickle-shaped");
    set_long("This sickle-shaped boat is the Corran, a ship " +
      "that travels between the villages of Port Macdunn and " +
      "Grey Havens. With the aft and fore sections of the vessel " +
      "jutting upward from out of the water, it looks rather " +
      "odd. A series of slim sails is attached to its mast.\n");
    add_item(({"sections","aft sections","fore sections"}),
      "They jut upwards from out of the water.\n");
    add_item(({"aft section","fore section","aft","fore"}),
      "It juts upward from out of the water, creating one " +
      "hook of the sickle-shape.\n");
    add_item("mast","The mast supports a small look-out.\n");
    add_item(({"look-out","small look-out"}),"The small " +
      "look-out is used to see far distances.\n");
    add_item(({"series of slim sails","series","slim sails",
        "sails"}),"The slim sails propel the ship to its " +
      "destinations.\n");
    add_item("sail","No particular one stands out.\n");
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

