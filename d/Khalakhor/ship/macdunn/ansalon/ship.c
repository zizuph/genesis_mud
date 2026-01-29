/* File:          /d/Khalakhor/ship/macdunn/ansalon/ship.c
 * Creator:       Teth
 * Date:          April 13, 1997
 * Modifications:
 * Purpose:       This is the Macdunn-Kalaman, or Khalakhor-Ansalon
 *                ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/ansalon/
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
        MACDUNN_DIR + "pier2",
        MACDUNN_DIR + "harbour",
        MACDUNN_DIR + "sea1",
        MACDUNN_DIR + "sea2",
        MACDUNN_DIR + "sea3",
        MACDUNN_DIR + "sea4",
        MACDUNN_DIR + "sea_kalaman",
        KALAMAN_PIER,
        MACDUNN_DIR + "sea_kalaman",
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
    set_name("galley");
    add_name(SHIP_NAME);
    add_name("ship");
    add_name("boat");
    add_adj("imposing");
    add_adj("wooden");
    set_long("This imposing wooden galley is the Bonnie Lass, a ship " +
      "that runs between the port towns of Port Macdunn and " +
      "Kalaman. It has a canvas sail, and no oars can be seen. " +
      "Its sturdy wooden structure allows it to survive ocean " +
      "storms.\n");
    add_item(({"sail","canvas sail"}),"It is aloft!\n");
    add_item(({"structure","sturdy structure","wooden structure"}),
      "The boat is made of sturdy white oak, a favoured wood of " +
      "shipwrights.\n");
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

/*
 * Function name: give_leave_warning
 * Description:   This function is here to give the players a warning
                  before the ship leaves.
 */
void
give_leave_warning()
{
    if (query_captain())
        query_captain()->command("emote shouts: All board the Bonnie Lass," +
          " we sail in 20 seconds!");
}
