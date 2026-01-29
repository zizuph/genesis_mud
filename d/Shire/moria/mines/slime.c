#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("Slimy room");
    set_long(
	"This is the Room of Slime. The walls are covered with a thick layer "+
	"of green slime and the smell is awful! The only exits are east and "+
	"west.");

    add_item(({"walls","slime"}),
	"Yuck! You wouldn't even touch this layer of green slime!");
    add_item("smell", "The slime smells awful!");
    EAST("dirthole");
    WEST("mining/mining.1");
}
