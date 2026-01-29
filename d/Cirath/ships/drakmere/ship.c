 /* /d/Cirath/ships/drakmere/ship.c
  * The Tyr-Drakmere line.
  * Decius, October 1997
  */

#pragma save_binary
#pragma strict_types

inherit "/d/Cirath/ships/drakmere/std/ship";

#include <stdproperties.h>
#include "ship.h"
#include "/sys/cmdparse.h"

void
create_ship()
{
  object cap;

  setuid();
  seteuid(getuid());
  set_deck(SHIPS + "deck");

  cap = clone_object(SHIPS + "captain.c");

  set_captain(cap);

  set_places_to_go(({
    TYR_PORT,
    DESERT1,
    DESERT2,
    MOUNTAINS1,
    MOUNTAINS2,
    FOOTHILLS,
    PLAINS,
    FOREST1,
    FOREST2
    KALAD_PORT,
    FOREST2,
    FOREST1,
    PLAINS,
    FOOTHILLS,
    MOUNTAINS2,
    MOUNTAINS1,
    DESERT2,
    DESERT1}));

  set_time_between_stops(({
    15,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    15,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3}));

  set_ticket_id("tyr-drakmere line");
  set_board_enabled(1);
  set_name("wagon");
  add_name("ship");
  add_name("caravan");
  add_adj("mekillot");
  add_adj("lumbering");
  set_short("lumbering mekillot wagon");
  set_long("This is a heavily armoured wagon pulled by a "+
    "large mekillot. It seems to be big enough to carry "+
    "both cargo and passengers.\n");

  add_item(({"mekillot","lizard"}),"This is a mighty lizard "+
    "of about 30 feet in length, and weighing several tons. "+
    "A thick shell covers its head and back, and a huge "+
    "snapping mouth promises a quick demise to the unwary.\n");

}

int
board(string what)
{
  object ticket, *tmp;

  if(!board_enabled)
    return 0;
  if(what && (!sizeof(tmp = FIND_STR_IN_OBJECT(
    what,ENV(TP))) || TO != tmp[0]))
    return 0;
  if(TP->query_average_stat() >= 20)
    return ::board(what);
  write("You board the caravan wagon.\n");
  environment(TP)->set_dircmd(what);
  TP->move_living("boarding the caravan wagon",query_deck()[0]);
    return 1;
}
