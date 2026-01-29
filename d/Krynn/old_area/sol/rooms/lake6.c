
#include "../local.h";

inherit SWIM_ROOM;

#include <ss_types.h>

void
create_swim_room() 
{
    set_long("The road snakes around the lake, following its shore. " +
	     "There is a break in the trees to the southwest, where you " +
	     "can spot an old rotten dock.\n");
    add_exit(ROOM + "dock","southwest",0);
    add_exit(ROOM + "lake7","north",0);
    add_exit(ROOM + "lake5","southeast",0);
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
