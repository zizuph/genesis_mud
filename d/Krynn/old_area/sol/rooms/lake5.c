
#include "../local.h";

inherit SWIM_ROOM;

void
create_swim_room() 
{
    set_long("As you continue along this ever-darkening lakeside road, your " +
	     "feeling of unease increases. Gnarled tree roots break up your " +
	     "path, making progess slow, and the canopy of foliage above " +
	     "you blocks out most light, leaving you with a dark sense of " +
	     "uncertainty.\n");
    add_exit(ROOM + "lake4","east",0);
    add_exit(ROOM + "lake6","northwest",0);
    add_item(({"army"}),
	     "You can't see anything, but that is not nessesary. " +
	     "You aren't stupid.\n");
    add_item("mountains",
	     "The mountains on the other side of the lake look majestic and " +
	     "inspiring. You sigh deeply, hoping beyond hope to LIVE to " +
	     "visit them some day.\n");
    add_item("wilderness",
	     "Just kidding about the wilderness soothing your soul. This " +
	     "place gives you the creeps. It's dark and nasty. The woods " +
	     "to the east of you seem to have eyes, and you walk along the " +
	     "path with your guard up.\n");
}
