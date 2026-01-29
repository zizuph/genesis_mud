/* Tantallon coded by Nick */

#include "local.h"

inherit TANTALLON_OUTSIDE;

void
create_tantallon_room()
{
    set_short("On south Bridge");
    set_long("You are standing on a stone bridge. North you see a small city. Under " +
	     "the bridge you hear water running. Walking south will take you into " +
	     "the mountains.\n");
    
    add_item("city",
	     "From here you get a good view at the city, and you directly decide to " +
	     "stop calling this place for a city. It looks much more like a " +
	     "village. The first thing that strikes you is that there are no " +
	     "houses. Instead there are several tents. There is also a dark evil " +
	     "glow about the small village. Who knows what awaits there.\n");
    add_item("bridge",
	     "It's an old fashioned stone bridge, it looks quite safe.\n");
    add_item(({"river", "water"}),
	     "You lean over the bridge to get a look of it. You can see some fish " +
	     "swimming around.\n");
    add_item("fish",
	     "The fish moves quickly in the water.\n");
    add_item("mountains",
	     "They sure are vast.\n");
    
    add_exit(TDIR + "city24", "north", 0);
    add_exit(ROOM_TO_SOLACE, "south", 0);
}
