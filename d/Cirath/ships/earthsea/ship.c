 // /d/Cirath/ships/earthsea/ship.c
 // The Tyr-Earthsea line.
 // Decius, February 1998.


#pragma save_binary
#pragma strict_types

inherit "/d/Cirath/ships/earthsea/std/ship";

#include <stdproperties.h>
#include "ship.h"
#include "defs.h"
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
  AIR8,
  AIR7,
  AIR6,
  AIR5,
  AIR4,
  AIR3,
  AIR2,
  AIR1,
  EARTHSEA_PORT,
  AIR1,
  AIR2,
  AIR3,
  AIR4,
  AIR5,
  AIR6,
  AIR7,
  AIR8}));

  set_time_between_stops(({
    15,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    15,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2}));

  set_ticket_id("tyr-earthsea line");
  set_name("roc");
  add_name("bird");
  set_board_enabled(1);
  add_name("ship");
  add_adj("fierce");
  set_short("fierce roc");
  set_long("This is a huge fearsome bird resembling an "+
    "eagle with dark brown plumage. Leather saddles are "+
    "strapped to it, allowing passengers to ride.\n");

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
  write("You climb onto the roc and strap the belt around "+
    "yourself.\n");
  environment(TP)->set_dircmd(what);
  TP->move_living("climbing onto the roc",query_deck()[0]);
    return 1;
}
