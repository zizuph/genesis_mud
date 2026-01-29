/*
 *
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_DRAGONSLAIR;


void
create_dragonslair_inside()
{
    INDOORS;
	
    NO_STEEDS;
	
	set_short("A branching cave tunnel.");
	
	set_long("Here the tunnel splits in two. One fork leads west, and "
		+"the tunnel curves ahead to the northeast. Judging by the sounds "
		+"an encampment has been set up to the west, and you can make out "
		+"the glow of torchlight in that direction. The tunnel continues "
		+"to travel deeper into the mountain to the northeast, and the acrid "
		+"smell emanates strongly from that direction. Stalactites hang from "
		+"the ceiling here, dripping water on the floor.\n");
		
	add_item(({"smell", "acrid smell", "rotten smell"}),
		"The smell of death is stronger here. It hangs heavy on the air, "
	   +"and reminds you of a rotting corpse. You must be getting closer "
	   +"to the source.\n");
	add_item(({"tunnel"}),
		"Which tunnel? The west tunnel or northeast tunnel?\n");
	add_item(({"west tunnel"}),
		"The tunnel continues in a straight line to the west. In the distance "
	   +"you can make out torchlight, and hear the sounds of creatures moving.\n");
	add_item(({"northeast tunnel"}),
		"This tunnel curves slightly and continues into the mountain in a "
	   +"northeasternly direction. The rotten smell on the air seems to come from "
	   +"this tunnel.\n");
	add_item(({"cave"}),
		"The mouth of the cave is behind you, and the cave continues deeper "
	   +"into the mountain ahead.\n");
	add_item(({"stalactites"}),
	    "The stalactites hang down from the ceiling, and occasionally a drop "
	   +"of water falls from one. Small pools have formed where the water "
       +"falls.\n");
    add_item(({"water", "pools", "pool"}),
		"The water comes from the ceiling, running down the stalactites "
	   +"and pooling as it falls on the ground. Some moss has developed in one "
	   +"of the pools.\n");
	add_item(({"moss"}),
		"This simple green moss has grown where the water has pooled on the floor.\n");
	add_item(({"ground", "floor"}),
		"The stone floor of the cave has been smoothed naturally over time. "
	   +"it slopes downwards very slightly here,\n");
	add_item(({"ceiling"}),
		"The ceiling is about twenty feet above the ground here. Stalactites "
	   +"reach down towards the ground, occasionally dropping water into "
	   +"small pools on the ground.\n");
		
    reset_faerun_room();
	
    add_exit(DRAGON_DIR + "dr1", "south");

}


void
reset_faerun_room()
{

}