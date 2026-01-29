inherit "/d/Genesis/ship/ship";
#include "local.h"
#include <cmdparse.h>
#include <macros.h>

void add_tour(mapping tour);


int someone_boarded = 0;
mapping tours = ([]);

void
create_multi_destination_ship()
{
}

void
create_ship()
{
    object cap;

    if (!IS_CLONE)
      return;
    seteuid(getuid());

    create_multi_destination_ship();

    set_cabin(CABIN);
    add_cabin(CABIN2);
    set_deck(DECK);
    add_deck(DECK2);
    cap = clone_object(CAPTAIN);
    set_captain(cap);
    
    set_ticket_id(TICKET_NAME);
    set_name("ship");
    add_name(SHIP_NAME);
    add_adj("large");
    add_adj("ocean-going");
    add_adj("pirate");
    set_long("This is a large ocean-going pirate ship. " +
	     "You see 15 oars sticking out on one side, and guess the number is " +
	     "the same on the other side. The wooden ship looks very well " +
	     "crafted. Nothing at all seems to indicate the destinations of this " +
	     "ship.\n");
    add_prop(OBJ_I_LIGHT,1);


    add_tour("emerald":({ SECRETPIER,      26,
			  BRANCHALA_BAY,    7,
			  OPEN_SEA,         7,
			  OPEN_SEA,         8,
			  /*... to and from Emerald ...*/

			  PIER_ON_EMERALD, 26,

			  /* */
			  OPEN_SEA,         7,
			  OPEN_SEA,         5,
			  BRANCHALA_BAY,    5 }));
    add_tour("kalad":({ SECRETPIER,        26,
			  BRANCHALA_BAY,    7,
			  OPEN_SEA,         6,
			  OPEN_SEA,         7,

			  /*... to and from Kalad ...*/
			  KALADSEA1,        4,
			  KALADSEA2,        4,
			  KALADSEA3,        4,
			  KALADSEA4,        4,
			  KALADSEA5,        4,
			  KABAL_ON_KALAD,  26,
			  KALADSEA5,        4,
			  KALADSEA4,        4,
			  KALADSEA3,        4,
			  KALADSEA2,        4,
			  KALADSEA1,        4,
			  /* */

			  OPEN_SEA,         7,
			  OPEN_SEA,         9,
			  BRANCHALA_BAY,    5 }));
    
    add_tour("avenir":({ SECRETPIER,       26,
			  BRANCHALA_BAY,    7,
			  OPEN_SEA,         8,
			  OPEN_SEA,         7,
			  /*... to and from Avenir ...*/

			  PORT_ON_AVENIR,  26,

			  /* */
			  OPEN_SEA,         7,
			  OPEN_SEA,         5,
			  BRANCHALA_BAY,    5 }));
    add_tour("terel":({ SECRETPIER,        26,
			  BRANCHALA_BAY,    7,
			  OPEN_SEA,         7,
			  OPEN_SEA,         8,
			  /*... to and from Terel ...*/

			  PIER_ON_TEREL,   26,

			  /* */
			  OPEN_SEA,         7,
			  OPEN_SEA,         8,
			  BRANCHALA_BAY,    5 }));
    
    add_tour("kalaman":({ SECRETPIER,      26,
			  BRANCHALA_BAY,    7,
			  OPEN_SEA,         7,
			  OPEN_SEA,         8,
			  /*... to and from Kalaman ...*/

			  PIER_ON_KALAMAN, 26,

			  /* */
			  OPEN_SEA,         7,
			  OPEN_SEA,         8,
			  BRANCHALA_BAY,    5 }));
    
    add_tour("tharbad":({ SECRETPIER,
			  BRANCHALA_BAY,
			  OPEN_SEA,
			  OPEN_SEA,
			  /*... to and from Tharbad/Gondor ...*/
			  "/d/Gondor/bay/openwater2",
			  "/d/Gondor/bay/openwater",
			  "/d/Gondor/gwathlo/mouth",
			  "/d/Gondor/gwathlo/londdaer",
			  "/d/Gondor/gwathlo/sriver2",
			  "/d/Gondor/gwathlo/sriver1",
			  "/d/Gondor/gwathlo/tharbad",
			  PIER_ON_THARBAD,
			  "/d/Gondor/gwathlo/tharbad",
			  "/d/Gondor/gwathlo/sriver1",
			  "/d/Gondor/gwathlo/sriver2",
			  "/d/Gondor/gwathlo/londdaer",
			  "/d/Gondor/gwathlo/mouth",
			  "/d/Gondor/bay/openwater",
			  "/d/Gondor/bay/openwater2",
			  /* */
			  OPEN_SEA,
			  OPEN_SEA,
			  BRANCHALA_BAY,
			       26,
				7,
				7,
				8,
				/* */
				2,
				2,
				2,
				2,
				2,
				2,
				2,
				26,
				2,
				2,
				2,
				2,
				2,
				2,
				2,
				/* */
				7,
				8,
				5
			  }));
    add_tour("pelargir",({ SECRETPIER,
			  BRANCHALA_BAY,
			  OPEN_SEA,
			  OPEN_SEA,
			  /*... to and from Pelargir/Gondor ...*/
			  "/d/Gondor/bay/openwater",
			  "/d/Gondor/bay/eshore2",
			  "/d/Gondor/anduin/mouth",
			  "/d/Gondor/anduin/pelargir",
			  PIER_ON_PELARGIR,
			  "/d/Gondor/anduin/pelargir",
			  "/d/Gondor/anduin/mouth",
			  "/d/Gondor/bay/eshore2",
			  "/d/Gondor/bay/openwater",
			  /* */
			  OPEN_SEA,
			  OPEN_SEA,
			  BRANCHALA_BAY,
			     26,
				7,
				7,
				8,
				/* */
				2,
				2,
				2,
				2,
				26,
				2,
				2,
				2,
				2,
				/* */
				7,
				8,
				5
			  }));
}

int
board(mixed what)
{
    int ret;

    NF("The ship doesn't seem to be going anywhere right now. Maybe you should " +
       "speak with the captain first.\n");
    if (!board_enabled)
      return 0;

    NF("Board what?\n");
    ret = ::board(what);
    if (ret)
      someone_boarded = 1;
    return ret;
}

void
stop_ship(string why)
{
    query_captain()->reset_destination();
    set_board_enabled(0);
    ::stop_ship(why);
}


void
sail_away_out_on_the_open_sea()
{
    if (call_no < 1 &&
	file_name(environment(query_captain())) == SECRETPIER &&
	!someone_boarded)
    {
	stop_ship("");
	query_captain()->command("say Hmm. Looks like there's " +
				 "no goods to ship right now. " +
				 "The trip is cancelled!");
    }
    else
      ::sail_away_out_on_the_open_sea();
    someone_boarded = 0;
}

void
add_tour(string dest, mixed* tour)
{
    tours += ([dest:tour]);
}

int
set_tour(string dest)
{
    mixed* tour = tours[dest];
    if (!tour)
      return 0;
    
    set_places_to_go(filter(tour,stringp));
    set_time_between_stops(filter(tour,intp));
    return 1;
}


mixed
query_destinations()
{
    return m_indexes(tours);
}
