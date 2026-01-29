#include "defs.h"

CONSTRUCT_ROOM {
    set_short("A terrace in form of a small round room.");
    set_long("A terrace in form of a small round room. In the west wall "+
	     "there is a smooth hole, while in the floor there is a "+
	     "miserable built down-leading passage.\n");
    add_item(({ "terrace", "room" }),
	"This seems like a terrace actually, though it perhaps is not. "+
	"Who can imagine what the dwarves really made?");
    add_item(({"floor", "passage"}),
	"It leads down into the mines.");
    add_item(({"hole","wall","west wall","walls"}),
	"There is a hole there leading into some stairs.");
    add_item(({"stair-case"}),
	"It leads up. You can try to climb up there.");
    EXIT("suddenst","down");
    EXIT("gstairs1","west");
}
