// name:          Avatar
// creator(s):    Cirion, May 1996
// last update:   
// purpose:       Ship line between the bazaar in Sybarus to Kalad
// note:
// bug(s):
// to-do:   

#pragma save_binary

inherit "/d/Genesis/ship/ship";

#include <cmdparse.h>
#include "/d/Avenir/common/ships/ship.h"

void create_ship()
{
    object cap;

    if (!IS_CLONE)
      return;

    set_name("ship");
    add_name("Avatar");
    add_adj("small");
    LONG("It is a long, narrow ship, made from stained hardwood. The deck is "
        +"slightly curved downwards, giving the whole ship a sturdy and "
        +"tough appearance. The is some writing on the prow.\n");
    add_item(({"prow","front"}),"The front of the ship curves upwards, "
        +"giving it a mean and sturdy appearance. Written on the side "
        +"is 'Avatar'.\n");
    ACI(({"prow","front","word","words","writing"}),"read","'Avatar'\n");

    set_deck(KALAD_DIR + "deck");
    set_ticket_id("_kalad_bazaar_ticket");
    seteuid(getuid());
    cap = clone_object(KALAD_DIR + "captain");
    cap->equip_me();
    set_captain(cap);
    set_callout_fq(1);
    set_places_to_go(({
      /* Pier in Bazaar */
      BAZAAR + "extr/k_landing",
      SEA + "darksea1",
      SEA + "darksea2",
      SEA + "darksea3",
      SEA + "darksea4",
      SEA + "darksea5",
      SEA + "d_sea_n1",
      SEA + "d_sea_n2",
      SEA + "d_sea_n3",
      SEA + "d_sea_n4",
      SEA + "d_sea_n5",
      SEA + "d_sea_n6",
      SEA + "d_sea_n7", }));

    set_time_between_stops(({
      60,
      10,
      10,
      10,
      10,
      10,
      10,
      10,
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
    cap = clone_object(SPAR_DIR + "captain");
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
  
  if(!board_enabled)
    return 0;
  if (what && (!sizeof(tmp = FIND_STR_IN_OBJECT(what,
      environment(this_player()))) || this_object() != tmp[0]))
    return 0;
  if (this_player()->query_average_stat() >= 20) 
    return ::board(what);

  // free passage for newbies
  write("You board the small ship.\n");
  environment(this_player())->set_dircmd(what);
  TP->move_living("boarding the small ship", query_deck()[0]);
  return 1;
}