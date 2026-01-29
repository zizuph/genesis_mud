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
	
    set_short("Just inside a cave entrance.");
	
    set_long("This is just inside the mouth of the cave. Stalactites hang " 
	    +"down from the ceiling, dripping water on the ground. An acrid smell " 
		+"hangs in the air, making it difficult to breathe. Light streams in "
		+"from the entrance, illuminating the dark tunnel ahead. The cave seems "
		+"to continue further into the mountain.");
		
    add_item(({"mouth", "cave mouth", "entrance", "opening"}),
        "The mouth of the cave leads out into the forest. You can see the " 
		+"trees of the forest beyond the mouth, and the light streams in "
		+"through the opening.\n");
	add_item(({"smell", "acrid smell", "air"}),
		"The smell of death hangs heavy on the air. It smells of decay "
	   +"and reminds you of a rotting corpse.\n");
	add_item(({"light"}),
		"The light streams in from the mouth of the cave, providing some "
	   +"illumination.\n");
	add_item(({"tunnel"}),
		"The tunnel leads from the mouth of the cave further into the "
	   +"mountain. You think you might be able to hear some sounds in the "
	   +"distance, but you can't make out any details.\n");
	add_item(({"cave"}),
		"You are in the mouth of the cave. On the other side is the forest, "
	   +"and the cave continues as a tunnel deeper into the mountain.\n");
	add_item(({"stalactites"}),
	    "The stalactites hang down from the ceiling, and occasionally a drop "
	   +"of water falls from one. Small pools have formed where the water "
       +"falls.\n");
    add_item(({"water", "pools", "pool"}),
		"The water comes from the ceiling, running down the stalactites "
	   +"and pooling as it falls on the ground.\n");
	add_item(({"ground", "floor"}),
		"The stone floor of the cave has been smoothed naturally over time.\n");
	add_item(({"ceiling"}),
		"The ceiling is about fifteen feet above the ground here. Stalactites "
	   +"reach down towards the ground, occasionally dropping water into "
	   +"small pools on the ground.\n");

    reset_faerun_room();
	
    add_exit(DRAGON_DIR + "dr2", "north");
}


void
reset_faerun_room()
{

}


