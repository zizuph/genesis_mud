inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Cave entrance");
	set_long(break_string("You are outside a huge cave and just by the great sea Tjurken "+
	"It is an amazing sight water as far as you can see. well it might possibly be an island"+
	"somwhere out there. The ground is anyhow full of garbage and driftwood. This seems to be some "+
	"kind of secret harbour. Used by smugglers long time ago. Or is it still in use? \n",70));
	add_exit(DRYPLAIN+"dpac1","west");
}