#include "forest.h"

create_forest()
{
    set_short("By some old fallen trees");
    set_long(
	"Here you have reached a dense vegetation of old fallen trees. "+
	"They lie in a random pattern hereabout, but you see most of "+
	"them in the north, preventing you from the northern and "+
	"northeastern exits. Though you would seem to be able to go "+
	"in any other direction.\n");

    NORTHWEST("f0003");
    WEST("f0002");
    SOUTHWEST("f0001");
    SOUTH("f0101");
    SOUTHEAST("f0201");
    EAST("f0202");
}
