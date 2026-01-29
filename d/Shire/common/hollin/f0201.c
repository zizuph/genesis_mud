#include "forest.h"

create_forest()
{
    set_short("River bank of Greyflood");
    set_long(
	"Here on the river bank of mighty Greyflood, you see that "+
	"the river slowly flows from the north to the south. It is "+
	"still possible to follow the bank, or go into the forest "+
	"in the west, but you would not dare to cross it. The stream "+
	"is simply too powerful.\n");

    NORTH("f0202");
    NORTHWEST("f0102");
    WEST("f0101");
    SOUTHWEST("f0100");
    SOUTH("f0200");
}
