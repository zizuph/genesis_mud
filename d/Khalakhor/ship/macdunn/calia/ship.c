/* File:          /d/Khalakhor/ship/macdunn/calia/ship.c
 * Creator:       Teth
 * Date:          April 15, 1997
 * Modifications: November 11, 1997, Teth, added support
 * Purpose:       This is the Macdunn-Gelan, or Khalakhor-Calia
 *                ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/calia/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/ship";
#include "local.h"
#include <cmdparse.h>
#include "/d/Khalakhor/sys/properties.h"

public void
create_ship()
{
    object cap;    
    seteuid(getuid());
    set_deck(DECK);
    cap = clone_object(CAPTAIN);
    cap->arm_me();
    set_captain(cap);
    set_places_to_go(({
        MACDUNN_DIR + "pier6",
        MACDUNN_DIR + "harbour",
        MACDUNN_DIR + "sea1",
        MACDUNN_DIR + "sea2",
        MACDUNN_DIR + "sea3",
        MACDUNN_DIR + "sea4",
        MACDUNN_DIR + "sea_gelan",
        GELAN_PIER,
        MACDUNN_DIR + "sea_gelan",
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
    add_adj("fishing");
    set_long("This fishing boat is the Cuinnsear, a dagger-shaped " +
      "fishing vessel that occasionally takes passengers between " +
      "Port Macdunn and Gelan. Although small, this ship does " +
      "appear to be able to withstand an ocean storm, because of " +
      "its unique shape.\n");
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
    if (this_player()->query_prop(LIVE_I_ROCK_BOATS))
    {
        find_living("cian")->command("say I will not " +
          "allow those who rock my boat to board it!");
        notify_fail("You are apparently not permitted to " +
          "board the fishing boat.\n");
        return 0;
    }           
    if (this_player()->query_average_stat() >= 15 &&
      this_player()->query_race() != "hobbit")
    {
        return ::board(what);
    }
    write("You board the ship.\n");
    environment(this_player())->set_dircmd(what);
    this_player()->move_living("boarding the ship", query_deck()[0]);
    return 1;
}

