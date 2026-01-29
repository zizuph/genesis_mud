#include "forest.h"

create_forest()
{
    set_short("By a large stone cliff");
    set_long(
	"Here, on your western side there is a large stone cliff. It looks like "+
	"it is possible to climb, but why would you? There seems not to be "+
	"anything interesting there except from the usual moss, mushrooms "+
	"and undergrowth. The cliff continues to the north from here.\n");

    NORTH("f0003");
    EAST("f0102");
    SOUTHEAST("f0101");
    SOUTH("f0001");
}
