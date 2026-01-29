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
	
	set_short("A tunnel in a mountain.");
	
	set_long("The tunnel grows darker as it continues deeper "
		+"into the mountain, and the ceiling is slowly getting "
		+"higher. The stalactites hanging down are reminiscent "
		+"of the teeth of a large beast, creating the illusion "
		+"of entering the maw of a monster. The smell of death is "
		+"choking the air. Large pools of water gather underneath "
		+"the stalactites, where a strange green moss grows.\n");
		
}