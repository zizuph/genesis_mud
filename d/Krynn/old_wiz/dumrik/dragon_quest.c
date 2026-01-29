
/* Dragon_quest.c   coded by Dumrik  1995-09-04    13.51            */
/* This object is here to fix so that the dragon i the dragon quest */
/* "harasses" the village of Solace once per hour, and leaves and   */
/* enters his cave once every 10 minutes for 10 minutes             */

/* /Dumrik                                                          */


#include "/d/Krynn/solamn/vin_mount/dragon_quest/local.h"
#include "/d/Krynn/common/defs.h"
#include TIME_FLOW
#define DEBUG(x)    find_living("dumrik")->catch_msg(x);

void add_flow() {
  ADD_EVENT("begin cave homecoming",
	    "dragon return to its cave",
	    "fix_dragon");

  ADD_EVENT("begin cave leaving",
	    "dragon leave its cave",
	    "remove_dragon");

  ADD_EVENT("begin solace harass",
	    "solace being harassed",
	    "begin_solace_sequence");

  ADD_PERIOD("solace being harassed",
	     ({3300,600}),
	     "begin cave homecoming",
	     ({""}));

  ADD_PERIOD("dragon returned to his cave",
	     600,
	     "begin cave leaving",
	     ({solace being harassed}));

  ADD_PERIOD("dragon away from cave",
	     600,
	     "begin cave homecoming",
	     ({solace being harassed}));

  INIT_THIS_THREAD("begin cave homecoming");
}

void fix_dragon() { 
  ROOM_DIR + "dragon_cave"->fix_dragon();
}

void remove_dragon() { 
  ROOM_DIR + "dragon_cave"->remove_dragon(); 
}

void begin_solace_sequence() { 
  ROOM_DIR + "dragon_cave"->begin_solace_sequence();
}






