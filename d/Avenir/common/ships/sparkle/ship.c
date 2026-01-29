// -*-C++-*-
// name: Melancholy /d/Avenir/common/ships/sparkle/ship.c
// creator(s):    Tepisch   Oct 1994
// last update:   Boriska, Mar 23 1995
// purpose:       To bring people to Avenir from Sparkle   
// note:
// bug(s):
// to-do:   

#pragma save_binary

inherit "/d/Genesis/ship/ship";

#include <cmdparse.h>
#include "/d/Avenir/common/ships/ship.h"

void
create_ship()
{
    object cap;

    if (!IS_CLONE)
      return;

    set_name("ship");
    add_name("Melancholy");
    add_name(({"bark", "barque"}));
    add_adj("ghostly");
    LONG("A ghostly-looking sailing ship with square-rigged masts. " +
	 "A decaying bust of indeterminate gender decorates the prow. " +
	 "On either side of the prow the letters 'G.S. MELANCHOLY' " +
	 "are printed in fading gold paint.\n");

    set_cabin(SPAR_DIR + "cabin");
    set_deck(SPAR_DIR + "deck");
    set_ticket_id("_staek_ticket");
    seteuid(getuid());
    cap = clone_object(SPAR_DIR + "captain");
    cap->equip_me();
    set_captain(cap);
    set_callout_fq(1); //I prefer to multiply by 1
    set_places_to_go(({
      /* put pier here*/
      PORT + "port11",
      SEA + "cave2",
      SEA + "cave3",
      SEA + "fiss3",
      SEA + "fiss4",
      SEA + "sea3",
      SEA + "sea2",
      /* to destination */
      /* put sparkle rooms here */
        "/d/Genesis/start/human/town/pier8",
      /* return home    */
      SEA + "sea2",
      SEA + "sea1",
      SEA + "fiss1",
      SEA + "fiss2",
      SEA + "cave1",
      SEA + "cave2", }));
    set_time_between_stops(({
      60, // wait here
      10,
      10,
      10,
      10,
      10,
      10,
      /* to destination */
      60, // wait there 
      /* return home    */
      10,
      10,
      10,
      10,
      10,
      10,
    }));
    enable_reset();
  }

void
reset_ship()
{
  object cap;
  if(!objectp(query_captain()))
    {
      cap=clone_object(SPAR_DIR + "captain");
      cap->equip_me();
      set_captain(cap);
      cap->move(query_deck()[0]);
      sail_away_out_on_the_open_sea();
    }
}

int
board(mixed what)
{
  object *tmp;
  
  if (!board_enabled)
    return 0;
  if (what && (!sizeof(tmp = FIND_STR_IN_OBJECT(what,
      environment(this_player()))) || this_object() != tmp[0]))
    return 0;
  if (this_player()->query_average_stat() >= 20) 
    return ::board(what);
  // free passage for newbies
  write("You board the Melancholy.\n");
  environment(this_player())->set_dircmd(what);
  TP->move_living("boarding the Melancholy", query_deck()[0]);
  return 1;
}
