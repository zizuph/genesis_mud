/*
 * newbie Genesis ship
 * Tapakah, 05/2009
 */

#include <cmdparse.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "newbie_ship.h"

inherit STDSHIP;

public int
board(string what)
{
    object ticket, *tmp;

    if (what && (!sizeof(tmp =
          FIND_STR_IN_OBJECT(what, environment(this_player()))) ||
        this_object() != tmp[0]))
    {
        return 0;
    }
    if (TP->query_average() >= MAX_PASSENGER_AVG)
    {
        find_living("cian")->command("say only small people " +
          "no larger than great adventurer can travel by this ship!");
        notify_fail("You are apparently too big to " +
          "board the fishing boat.\n");
        return 0;
    }           
    if (this_player()->query_average_stat() >= MAX_PASSENGER_AVG/2)
    {
        return ::board(what);
    }
    write("You board the ship.\n");
    environment(this_player())->set_dircmd(what);
    this_player()->move_living("boarding the ship", query_deck()[0]);
    return 1;
}
