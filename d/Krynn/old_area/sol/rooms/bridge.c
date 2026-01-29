/* created by Aridor, 08/12/94 */

#include "local.h"

inherit SOLACE_ROOM

void
create_solace_room()
{
    set_short("Haven Road bridge");
    set_long("You are standing on a small bridge across a river. It appears " +
	     "that the river comes from the great body of water visible " +
	     "to the north, then continues south where it meanders through " +
	     "the land. Further west along the road you can see a fork in " +
	     "the road. In the other direction, the road continues east. " +
	     "A few scattered bushes and trees are around you.\n");
    add_exit(HROAD + "road1","east",0,2);
    add_exit(HROAD + "xroad","west",0,2);
    add_item("bridge",
	     "It's a fairly small bridge made of wood. It looks safe to " +
	     "pass though.\n");
    add_item("river",
	     "This is Solace Stream, coming from Crystalmir Lake in the " +
	     "north and flowing due south towards some gorge which can " +
	     "only be imagined far in the south.\n");
    add_item(({"body","water","lake"}),
	     "This is Crystalmir Lake, even though it is quite some " +
	     "distance away, you can still imagine how big it is. " +
	     "Looking further north you can see " +
	     "dark clouds gathering high in the sky.\n");
    add_item("clouds",
	     "These are ordinary clouds, but they still look quite dark " +
	     "and menacing, even from this distance.\n");
    add_item("mountains",
	     "The mountains in the northwest are quite high and barren, " +
	     "and they are not very far away. To the east you can see the " +
	     "mountains only in the distance and you cannot make out any " +
	     "details.\n");
    add_item("road",
	     "It's a gravel road leading east and west away from the bridge.\n");
}
