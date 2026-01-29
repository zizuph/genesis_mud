#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("Round chamber");
    set_long(
	"You are in the Round Chamber. "+
	"There is a cold creeping draft of air from the south here, and a "+
	"another exit to the west.\n");
    add_item(({"air","draft","south exit"}),
	"The draft seems to come from the south through an exit in the wall.");
    add_item("west exit", "It leads somewhat east into another room.");
    add_item(({"chamber","room","walls","floor","ceiling",
	       "rocks","rock","rock-face","rock-faces"}),
	"This room is round, by which we mean having circular walls and "+
	"spherical ceiling. The room is roughly carved out of the mountain "+
	"and the rock-faces seems to be of hard granite.");
    SOUTH("lake_w");
    WEST("cross");
}
