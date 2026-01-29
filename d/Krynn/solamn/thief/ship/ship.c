inherit "/d/Genesis/ship/ship";
#include "local.h"
#include <cmdparse.h>
#include <macros.h>

#ifdef PIER_ON_EMERALD
void set_emerald_tour();
#endif
#ifdef KABAL_ON_KALAD 
void set_kalad_tour();
#endif
#ifdef PIER_ON_TEREL
void set_terel_tour();
#endif
#ifdef PIER_ON_KALAMAN
void set_kalaman_tour();
#endif
#ifdef PIER_ON_THARBAD
void set_tharbad_tour();
#endif
#ifdef PIER_ON_PELARGIR
void set_pelargir_tour();
#endif
#ifdef AVENIR_PORT_PATH
void set_avenir_tour();
#endif
#ifdef PIER_ON_GONT
void set_gont_tour();
#endif


int someone_boarded = 0;


void
create_ship()
{
    object cap;

    if (!IS_CLONE)
      return;
    seteuid(getuid());
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
/*
    add_prop(OBJ_I_FLOAT, 1); 
*/
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




#ifdef PIER_ON_EMERALD
void
set_emerald_tour()
{
    set_places_to_go(({	SECRETPIER,
			  BRANCHALA_BAY,
			  OPEN_SEA,
			  OPEN_SEA,
			  /*... to and from Emerald ...*/

			  PIER_ON_EMERALD,

			  /* */
			  OPEN_SEA,
			  OPEN_SEA,
			  BRANCHALA_BAY,
		    }));
    
    set_time_between_stops(({ 26,
				7,
				7,
				8,

				26,

				7,
				5,
				5
			  }));
}
#endif

#ifdef KABAL_ON_KALAD 
void
set_kalad_tour()
{
    set_places_to_go(({	SECRETPIER,
			  BRANCHALA_BAY,
			  OPEN_SEA,
			  OPEN_SEA,

			  /*... to and from Kalad ...*/
			  KALADSEA1,
			  KALADSEA2,
			  KALADSEA3,
			  KALADSEA4,
			  KALADSEA5,
			  KABAL_ON_KALAD,
			  KALADSEA5,
			  KALADSEA4,
			  KALADSEA3,
			  KALADSEA2,
			  KALADSEA1,
			  /* */

			  OPEN_SEA,
			  OPEN_SEA,
			  BRANCHALA_BAY,
		    }));
    
    set_time_between_stops(({ 26,
				7,
				6,
				7,

				4,
				4,
				4,
				4,
				4,
				26,
				4,
				4,
				4,
				4,
				4,

				7,
				9,
				5
			  }));
}
#endif

#ifdef PIER_ON_TEREL 
void
set_terel_tour()
{
    set_places_to_go(({	SECRETPIER,
			  BRANCHALA_BAY,
			  OPEN_SEA,
			  OPEN_SEA,
			  /*... to and from Terel ...*/

			  "/d/Terel/ships/sea2",
			  "/d/Terel/ships/sea1",
			  "/d/Terel/ships/bay",
			  PIER_ON_TEREL,
			  "/d/Terel/ships/bay",
			  "/d/Terel/ships/sea1",
			  "/d/Terel/ships/sea2",

			  /* */
			  OPEN_SEA,
			  OPEN_SEA,
			  BRANCHALA_BAY,
		    }));
    
    set_time_between_stops(({ 26,
				7,
				7,
				8,

				2,
				2,
				2,
				26,
				2,
				2,
				2,

				7,
				8,
				5
			  }));
}
#endif

#ifdef PIER_ON_KALAMAN
void
set_kalaman_tour()
{
    set_places_to_go(({	SECRETPIER,
			  BRANCHALA_BAY,
			  OPEN_SEA,
			  OPEN_SEA,
			  /*... to and from Kalaman ...*/

			  "/d/Krynn/solamn/splains/room/vriver1",
			  PIER_ON_KALAMAN,
			  "/d/Krynn/solamn/splains/room/vriver1",

			  /* */
			  OPEN_SEA,
			  OPEN_SEA,
			  BRANCHALA_BAY,
		    }));
    
    set_time_between_stops(({ 26,
				7,
				7,
				8,

				2,
				26,
				2,

				7,
				8,
				5
			  }));
}
#endif

#ifdef PIER_ON_THARBAD
void
set_tharbad_tour()
{
    set_places_to_go(({	SECRETPIER,
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
		    }));
    
    set_time_between_stops(({ 26,
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
}
#endif

#ifdef PIER_ON_PELARGIR
void
set_pelargir_tour()
{
    set_places_to_go(({	SECRETPIER,
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
		    }));
    
    set_time_between_stops(({ 26,
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
#endif

#ifdef AVENIR_PORT_PATH
void
set_avenir_tour()
{
    set_places_to_go(({	SECRETPIER,
			  BRANCHALA_BAY,
			  OPEN_SEA,
			  OPEN_SEA,
			  /*... to and from Sybarus/Avenir ...*/

			  "/d/Avenir/common/ships/sea/sea1",
			  "/d/Avenir/common/ships/sea/sea2",
			  "/d/Avenir/common/ships/sea/sea3",
			  AVENIR_PORT_PATH,
			  "/d/Avenir/common/ships/sea/sea3",
			  "/d/Avenir/common/ships/sea/sea2",
			  "/d/Avenir/common/ships/sea/sea1",

			  /* */
			  OPEN_SEA,
			  OPEN_SEA,
			  BRANCHALA_BAY,
		    }));
    
    set_time_between_stops(({ 26,
				7,
				7,
				8,
				/* */

				2,
				2,
				2,
				26,
				2,
				2,
				2,

				/* */
				7,
				8,
				5
			  }));
}
#endif

#ifdef PIER_ON_GONT
void set_gont_tour()
{
    set_places_to_go(({	SECRETPIER,
			  BRANCHALA_BAY,
			  OPEN_SEA,
			  OPEN_SEA,
			  /*... to and from Gont Port/Earthsea ...*/

			  "/d/Earthsea/ships/avenir_line/water3",
			  "/d/Earthsea/ships/avenir_line/water2",
			  "/d/Earthsea/ships/avenir_line/water1",
			  PIER_ON_GONT,
			  "/d/Earthsea/ships/avenir_line/water1",
			  "/d/Earthsea/ships/avenir_line/water2",
			  "/d/Earthsea/ships/avenir_line/water3",

			  /* */
			  OPEN_SEA,
			  OPEN_SEA,
			  BRANCHALA_BAY,
		    }));
    
    set_time_between_stops(({ 26,
				7,
				7,
				8,
				/* */

				2,
				2,
				2,
				26,
				2,
				2,
				2,

				/* */
				7,
				8,
				5
			  }));
}
#endif

