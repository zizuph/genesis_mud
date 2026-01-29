// -*-C++-*-
// name: Luminous /d/Avenir/common/ships/faerun/ship.c
// creator(s):    Lilith   Oct 1997
// last update:   Lucius 2008: Converted to Faerun line.
// purpose:       To bring people to Avenir from Faerun.
// note:
// bug(s):
// to-do:   
#pragma strict_types

inherit "/d/Genesis/ship/ship";

#include <cmdparse.h>
#include "../ship.h"

#define FAERUN  "/d/Faerun/ships/sparkle/"

private static object cap;

public void
create_ship(void)
{
    if (!IS_CLONE)
	return;

    set_name(({"ship", "Luminous", "vessel"}));
    set_adj(({"luminous", "sailing"}));
    set_long("A vaguely luminous vessel with two lateen-rigged masts. " +
	 "On either side of the prow the letters 'G.S. LUMINOUS' " +
	 "are printed in curling golden script.\n");

    set_deck(FRUN_DIR + "deck");
    set_cabin(FRUN_DIR + "cabin");
    set_ticket_id("_SybFrun_Ticket");

    cap = clone_object(FRUN_DIR + "captain");
    cap->equip_me();

    set_captain(cap);
    set_callout_fq(1); 

    set_places_to_go(({
      /* put pier here */
      PORT + "port14",
       SEA + "cave2",
       SEA + "cave3",
       SEA + "fiss3",
       SEA + "fiss4",
       SEA + "sea3",
       SEA + "sea2",
      /* to destination */
      FAERUN + "openwater4",
      FAERUN + "openwater3",
      FAERUN + "openwater2",
      FAERUN + "openwater1",
      FRUN_PORT,
      /* return home */
      FAERUN + "openwater1",
      FAERUN + "openwater2",
      FAERUN + "openwater3",
      FAERUN + "openwater4",
      SEA + "sea2",
      SEA + "sea1",
      SEA + "fiss1",
      SEA + "fiss2",
      SEA + "cave1",
      SEA + "cave2", }));

    set_time_between_stops(({
      60, // wait here
       6,
       6,
       6,
       6,
       6,
       6,
      /* to destination */
       6,
       6,
       6,
       6,
      60, // wait there 
      /* return home    */
       6,
       6,
       6,
       6,
       6,
       6,
       6,
       6,
       6,
       6,
    }));

    enable_reset();
}

public void
reset_ship(void)
{
    if (!objectp(query_captain()))
    {
        cap = clone_object(FRUN_DIR + "captain");
        cap->equip_me();

        set_captain(cap);
        cap->move(query_deck()[0]);
        sail_away_out_on_the_open_sea();
    }
}
