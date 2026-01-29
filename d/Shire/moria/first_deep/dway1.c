#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("Durin's Way");
    set_long("You are standing in a wide avenue called Durin's Way.\n" +
	     "It is remarkable to see this road. Once upon a time it " +
	     "was filled with dwarves, elves and humans travelling " +
	     "from east to the west from Rhovanion to Eregion. Now " +
	     "however, it is dark. Dark since the staggering light " +
	     "of the Dwarves died out as the Demon of Moria, the Bane "+
	     "of Durin, entered into the Mines and feriously slayed "+
	     "the Dwarves and forced all but a few to flee.\n");
    WEST("inn_chamber");
    EAST("dway2");
}
