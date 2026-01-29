inherit "/std/room.c";

#include "local.h"

void
create_room()
{
    set_short("A track north of Solace");
    set_long("You are wandering along a track north of Solace, and you " +
	     "are about to come out of the forest onto some plains. A " +
	     "few lone bushes are all the vegetation that can be found " +
	     "to your north, whereas a forest, even though it is a rather " +
	     "light one, is to your south. This dirt road doesn't look " +
	     "like it is being in much use recently, but you notice some " +
	     "tracks leading to and coming from the north.\n");
    add_item(({"track","road"}),
	     "This road doesn't look well travelled at all.\n");
    
    add_exit(SOLACE, "south");
    add_exit(PARENT + "newsea2", "north", "@@construction");
}

int
construction()
{
    write("Someone has planted a sign in the middle of the road and a " +
	  "barrier blocks the track. The sign reads: 'On behalf of " +
	  "your own security, this exit is currently closed.'\n");
    return 1;
}
