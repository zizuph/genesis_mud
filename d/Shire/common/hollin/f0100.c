#include "forest.h"

create_forest()
{
    set_short("In a gloomy forest");
    set_long(
	"You are in a large gloomy forest. You can hear now the sound "+
	"of a large river somewhat in the east. You cannot see it "+
	"from here, but it must be the Greyflood streaming down from "+
	"the regions in the far north. As you think of it, you realize "+
	"that the water must have traveled from the northern parts "+
	"of the Misty Mountains, which must be leagues from here. "+
	"Well, then it must be large, right? It probably continues "+
	"far down to the south through the whole of Eregion. You could "+
	"try to go in every direction from here.\n");
    WEST("f0000");
    NORTHWEST("f0001");
    NORTH("f0101");
    NORTHEAST("f0201");
    EAST("f0200");
/*    SOUTHEAST("f02-1");
      SOUTH("f01-1");
      SOUTHWEST("f00-1"); */
}
