#pragma save_binary

inherit "/d/Genesis/ship/ship";
#include <cmdparse.h>
#include "/d/Shire/common/defs.h"
#define AV_DIR "/d/Avenir/common/ships/sea/"
void
create_ship()
{
    object cap;    
    seteuid(getuid());
    set_cabin(SHIP_DIR + "ship3/cabin");
    set_deck(SHIP_DIR + "ship3/deck");
    cap=clone_object(SHIP_DIR + "ship3/captain");
    set_captain(cap);
    set_places_to_go(({
		       SHIP_DIR + "w6",
		       SHIP_DIR + "w5",
		       SHIP_DIR + "w4",
		       SHIP_DIR + "w3",
		       SHIP_DIR + "w2",
		       SHIP_DIR + "w1",
           AV_DIR + "sea1",
           AV_DIR + "sea2",
           AV_DIR + "sea3",
            "/d/Avenir/common/port/port12",
           AV_DIR + "sea3",   
           AV_DIR + "sea2",
           AV_DIR + "sea1",
		       SHIP_DIR + "w1",
		       SHIP_DIR + "w2",
		       SHIP_DIR + "w3",
		       SHIP_DIR + "w4",
		       SHIP_DIR + "w5",
		       SHIP_DIR + "w6",
           GHAVEN_DIR + "pier5"}));

           set_time_between_stops(({
			     2,
			     2,
			     2,
			     2,
			     2,
                             2,
                             2,
                             2,
                             2,
                            30,
                             2,
                             2,
                             2,
                             2,
                             2,
                             2,
                             2,
                             2,
                             2,
		 	     30}));
    set_ticket_id("the Grey Havens-Sybarus");
    set_name("ship");
    add_name("boat");
    add_adj("elegant");
    add_adj("elven");
    set_long("This elegant elven ship is obviously crafted in the "+
    "shipyards of Cirdan the Shipwright in Mithlond, or Grey Havens. "+
    "It is long and beautiful, covered from stem to stern with "+
    "elven jewels that shine like a silmaril in the noonday light.\n");
  enable_reset();
}

void
reset_ship()
{
  object cap;
  if(!objectp(query_captain()))
  {
    cap=clone_object(SHIP_DIR + "ship3/captain");
    set_captain(cap);
    cap->move(query_deck()[0]);
    sail_away_out_on_the_open_sea();
  }
}

int
board(string what)
{
    object ticket, *tmp;

    if (!board_enabled)
   return 0;
    if (what && (!sizeof(tmp =
                FIND_STR_IN_OBJECT(what, environment(TP))) ||
               TO != tmp[0]))
   return 0;
    if (TP->query_average_stat() >= 20)
   return ::board(what);

    write("You board the ship.\n");
    environment(TP)->set_dircmd(what);
    TP->move_living("boarding the ship", query_deck()[0]);
    return 1;
}