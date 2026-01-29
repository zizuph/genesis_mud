/* /d/Faerun/sunken_ruins/rooms/forest.c
 *
 * Nerull 2019
 *
 */
 
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "defs.h";

inherit STD_SUNKEN_OUTDOOR;

void
create_sunken_outdoor()
{
    set_short("Somewhere on a white sandy beach");
    
    set_extraline("Seawater rolls gently over your "
        +"feet and back into the ocean to the west. The sand is "
		+"soft, pearl-white and pristine, with no "
        +"signs of seaweed or other foreign objects disturbing the "
        +"almost perfect view. The white sandy beach keeps going "
		+"on southwards and northwards following the coast, only "
		+"separated by a dense forest to the west.");

    add_item(({"sloping platform","ledge"}),
        "The platform is less slippery than it should "
        +"be with all the falling snow. "
        +"It is as if it would be periodically maintained "
        +"with tiny rocks spread out "
        +"across it to ensure firm footing upon it.\n");
    
    add_exit(SUNKEN_ROOM_DIR + "beach.c", "northwest");
	add_exit("/d/Faerun/highroad/rooms/nrd07", "east");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}
