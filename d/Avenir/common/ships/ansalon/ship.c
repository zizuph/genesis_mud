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

    set_name("caravel");
    add_name("Odalisque");
    add_name(({"ship", "vessel"}));
    add_adj("battered");
    LONG("A battered sailing vessel with two lateen-rigged masts. " +
       "The triangular sails are striped with brilliant colours. "+
	 "On either side of the prow the letters 'G.S. ODALISQUE' " +
	 "are printed in curling golden script.\n");

    set_deck(ANSA_DIR + "deck");
    set_ticket_id("_SybAnsalon_Ticket");
    seteuid(getuid());
    cap = clone_object(ANSA_DIR + "captain");
    cap->equip_me();
    set_captain(cap);
    set_callout_fq(1); //I prefer to multiply by 1
    set_places_to_go(({
      /* put pier here */
      PORT + "port13",
      SEA + "cave2",
      SEA + "cave3",
      SEA + "fiss3",
      SEA + "fiss4",
//      SEA + "sea3",
//      SEA + "sea2",
      /* to destination */
      ANSA_SEA + "sea2",
      ANSA_SEA + "sea1",
      ANSA_PORT,
      /* return home */
      ANSA_SEA + "sea1",
      ANSA_SEA + "sea2",    
//      SEA + "sea2",
//      SEA + "sea1",
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
//      10,
//      10,
      /* to destination */
      60, // wait there 
      /* return home    */
      10,
      10,
//      10,
//      10,
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
      cap = clone_object(ANSA_DIR + "captain");
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
    if (this_player()->query_average_stat() >= 25) 
        return ::board(what);

    // free passage for newbies
    write("You board the Odalisque.\n");
    environment(this_player())->set_dircmd(what);
    TP->stop_fight();
    TP->move_living("boarding the Odalisque", query_deck()[0]);
    return 1;
}