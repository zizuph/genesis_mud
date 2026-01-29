/*
 * The Northern end of the High Road
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

//inherit BASE_ROAD;
inherit "/d/Faerun/highroad/bridge/std/base_road.c";

static object guard1, guard2, guard3, guard4, guard5;

void
create_road()
{
    set_short("gates of Neverwinter");
    set_extraline("You stand before Neverwinter, dwarfed by its massive walls. " +
    	"Entrance to the city is blocked by a huge closed gate with guardtowers on " +
    	"on each side. You can see some movement up on the battlements. The air " + 
    	"is filled with smoke and the stench of burned flesh. \n");

//	add_features(({"nw_city_n_close", "nw_gate", "nw_walls", "nw_battlements"}));

    reset_faerun_room();

    add_exit(BR_DIR + "nrd09", "south");

}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
	if (!guard1) {
		guard1 = clone_object(NPC_DIR + "sergeant");
		guard1 -> move (TO);
	}
	if (!guard2) {
		guard2 = clone_object(NPC_DIR + "random_guard");
		guard2 -> move (TO);
		guard1 -> team_join(guard2);
	}
	if (!guard3) {
		guard3 = clone_object(NPC_DIR + "random_guard");
		guard3 -> move (TO);
		guard1 -> team_join(guard3);
	}
	if (!guard4) {
		guard4 = clone_object(NPC_DIR + "random_guard");
		guard4 -> move (TO);
		guard1 -> team_join(guard4);
	}
	if (!guard5) {
		guard5 = clone_object(NPC_DIR + "random_guard");
		guard5 -> move (TO);
		guard1 -> team_join(guard5);
	}
}


