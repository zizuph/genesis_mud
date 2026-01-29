inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "/d/Emerald/defs.h"
#include "../../ctower.h"
 
void
create_ctower_room()
{
    set_short("Reflection canyon");
   
    set_long("The sky has gone completely black and "+
	"the ground seems to give off a subdued ghostly light.  "+
	"As your eyes adjust, you notice a spectral tower has "+
	"appeared. Perhaps it was there all along.\n");
   
    add_item(({"tower"}), "As you examine the tower more "+
	"thoroughly you notice that it seems to be giving off the light.  "+
	"There appears to be only one "+
	"entrance, a pitch black archway.  The only spot on the whole "+
	"tower that isn't glowing.  It doesn't look very inviting.\n" );
   
    add_item(({"crystal", "crystals", "ground"}), "The crystal "+
	"doesn't seem to be individual pieces but rather facets of a "+
	"larger whole.\n" );
   
    add_exit("entry", "enter");
}
