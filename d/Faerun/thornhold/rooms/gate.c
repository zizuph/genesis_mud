/*
 * Thornhold
 * -- Twire/Gnim June 2016
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_ROAD;
object guard_npc;

void
create_road()
{
	set_short("The Thornhold Gate");

	add_item(({ "yard", "down", "ground" }),
		"The yard is rutted with deep grooves and hooves that " +
		"suggest the passage of many wagons and horses.\n");
	
	add_item(({ "sea", "swords" }),
		"The Sea of Swords yawns off into the distance beyond the " +
		"cliff's edge. You can see ships approaching the Great " +
		"Harbor far to south as they approach the " +
		"City of Splendors.\n");
		
	add_item(({ "cliff", "west", "ledge" }),
		"The cliff ends several meters beyond the limits of the " +
		"west tower of Thornhold. You notice some sturdy rocks " +
		"jutting out from the edge. You may be able to climb " +  
	    "a narrow ledge leading to the cliff, should you " +
	    "possess the necessary skill.\n");

	add_item(({ "arch", "stone arch"}),
		"The arch is constructed of the same chiseled gray stone " +
		"bricks as the rest of the hold, with the exception of a " +
		"trapezoidal cornerstone at the peak of the arch.\n");

	add_item(({ "cornerstone", "crest" }),
		"The cornerstone is engraved with a crest shaped like a " +
		"shield trisected by three broad lines that meet in the " +
		"center.\n");
		
	add_item(({ "portcullis", "gate" }),
		"A portcullis is drawn up into the gate. You can see only " +
		"thick triangular spikes or wrought iron peeking down from " +
		"the arch. \n");
		
	add_item(({"keystone","capstone"}),
		"is a wedge-shaped stone piece at the apex of the arch. " +
		"Nothing special about this one.\n");
		
	add_item(({ "rocks", "rock" }),
		"Upon closer examination, the rocks look like they might " +
		"serve as footholds if you dared climb down.\n");
		
	add_item(({ "courtyard" }),
		"The courtyard is just beyond the gate to the north. " +
		"You can see manner of goods and wares beyond, " +
		"brought in by visiting caravans and travellers.\n");
		
	add_item(({ "towers", "tower" }),
		"Two towers flank the main gate, one to the east, " +
		"one to the west. They are tall and dotted with " +
		"narrow arrow slits at even intervals. The west tower is " +
		"built just on the edge of the sheer cliff overlooking the " +
		"Sea of Swords, while the east stands watch " +
		"over the Mere of Dead Men.\n");

	add_item(({ "slits", "slit" }),
		"The slits are typical of fortress towers, and are long " +
		"narrow openings through which archers might fire arrows " +
		"should invaders assault the fortress.\n");
		
	add_item(({ "mere", "Mere" }),
		"The mere is only visible from here to the southeast, " +
		"looking down between the rocks. Vast swamplands are a " +
		"quagmire of mud and death that loom below. The mere does " +
		"not look inviting.\n");
		
	add_item(({ "thornhold", "Thornhold", "hold", "fortress", "fort" }),
		"You stand at the main gate of the great " +
		"fortress of Thornhold.\n");
		
	add_extra_string_end("A stone arch frames the " +
		"Thornhold Gate. The gate itself is an iron portcullis, " +
		"drawn up to welcome visitors to the hold. Two round " +
		"stone towers flank the entrance, and to " +
	    "the north, you can enter an open-air courtyard. " +
	    "To the west, a narrow ledge hugs the western tower, " +
	    "beyond which expands a sweeping vista of the Sea of " +
	    "Swords.");
	
    reset_faerun_room();

    add_exit(ROOM_DIR + "courtyard_south",    "north");
    add_exit(ROOM_DIR + "thornhold_road_09",   "south");

    set_no_exit_msg(({"west"}),
    "You step onto the ledge leading around the west tower, and " +
    "find only unstable footing. It would take a more deliberate " + 
    "effort to proceed in that direction.\n");

    set_no_exit_msg(({"southwest"}),
    "You look down at the precipitous cascade of jagged rocks that " +
    "tumble towards the sea, finding no way to proceed in that " +
    "direction.\n");

    set_no_exit_msg(({"east", "southeast"}),
    "You see a gap in the rocks that yields to a treacherous " +
    "embankment leading to the Mere of Dead Men, but it is " +
    "littered with loose and treacherous rock that renders passage " +
    "in that direction impossible.\n");

    set_no_exit_msg(({"east", "northeast", "northwest"}),
    "The stout walls of Thornhold have been set strategically against " +
    "the jagged rocks of the environs, rendering the open gate the " + 
    "only point of entry into the fortress.\n");
    
    add_cmd_item(({"west", "cliff", "ledge"}),"climb","@@climb");
}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
    
    if ((!guard_npc))
    {
        guard_npc = clone_object(NPC_DIR + "dwarf_guard");
        guard_npc->move(this_object()); 
        guard_npc = clone_object(NPC_DIR + "dwarf_guard");
        guard_npc->move(this_object()); 
    } 
    
    set_searched(0);
}   


int climb()
{
    if(TP->query_skill(SS_CLIMB)>25)
    {
        TP->catch_msg("You skillfully climb along the narrow ledge " +
        "and make your way towards the cliffside.\n");
        TP->move_living("climbing along the precarious ledge that " +
        "hugs the western tower", "/d/Faerun/thornhold/rooms/cliffside");
        return 1;
    }
    if(TP->query_skill(SS_CLIMB)>10)
    {
        TP->catch_msg("You attempt to climb the precarious ledge, but " + 
        "find no secure footholds.\n");
        return 1;
    }
    TP->catch_msg("You are not skilled enough to climb the ledge.\n");
    return 1;
}