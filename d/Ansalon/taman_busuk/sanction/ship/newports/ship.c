/*
 * Revision history:
 * 25 Feb 2000, by Boron added support for the war, if the Knights hold the
 *                  other side, we are staying here! :)
 */
inherit "/d/Genesis/ship/ship";
#include "local.h"
#include <cmdparse.h>
#include "/d/Krynn/common/warfare/warfare.h"

void
create_ship()
{
    object cap;
    seteuid(getuid());
    set_cabin(CABIN);
    set_deck(DECK);
    cap = clone_object(CAPTAIN);
    set_captain(cap);
    set_callout_fq(4);
    set_places_to_go(({
    PIER,
    ROOM + "sea1",
    ROOM + "sea2",
    ROOM + "sea20",

    PIER2,
    ROOM + "sea20",
    ROOM + "sea2",
    ROOM + "sea1",
      }));

    set_time_between_stops(({
    18,
    3,
    6,
    3,

    18,
    3,
    6,
    3,
      }));

    set_ticket_id(TICKET_NAME);
    set_name("ferry");
    add_name("ship");
    add_name(SHIP_NAME);
    set_adj("lumbering");
    add_adj("troop");
    set_long("This lumbering troop ferry carries Dragonarmy troops to " +
        "and from Sanction. It has little of grace, but it looks sturdy " +
        "enough for the Newsea.\n");
}


board(what)
{
    object ticket, *tmp;


    if (!board_enabled)
        return 0;

    if (what && (!sizeof(tmp =
                        FIND_STR_IN_OBJECT(what, environment(this_player()))) ||
                                                this_object() != tmp[0]))
    {
        return 0;
    }

/*
    if (ARMYMASTER->army_in_area(WAR_AREA_NEWPORT) == KNIGHT_ARMY)
    {
       if (find_object(PIER) == environment(this_player()) )
        {
            write("This ship isn't going anywhere.\n");
            return 1;
        }
    }
*/
    else
        //start_ship(0);

    if (this_player()->query_average_stat() >= 20)
        return ::board(what);

    write("You board the ship.\n");
    environment(this_player())->set_dircmd(what);
    this_player()->move_living("boarding the ship", query_deck()[0]);

    return 1;
}

void
sail_away_out_on_the_open_sea()
{

/*
    if (ARMYMASTER->army_in_area(WAR_AREA_NEWPORT) == KNIGHT_ARMY)
    {
       if (find_object(PIER) == environment(this_player()) )
        {

            return;
        }
    }
*/

    ::sail_away_out_on_the_open_sea();

}