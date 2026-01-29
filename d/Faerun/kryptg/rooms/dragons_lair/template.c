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
		+"from the entrance, illuminating the dark tunnel ahead. The cave seems"
		+"to continue further into the mountain.");
    
	reset_faerun_room();
	
    add_exit(DRAGON_DIR + "dr2", "southeast");
}


void
reset_faerun_room()
{

}

