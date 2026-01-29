#include "defs.h"

CONSTRUCT_ROOM {
    set_short("This is a small cave filled with soil and pebbles.");
    set_long("This is a small cave filled with soil and pebbles. "+
	     "Unfortunately the only exit is south.\n");
    add_neg("search", "[here] [for] 'batmobile' / 'batman'",
	    "You've got to be kidding, right!!?!\n");
    EXIT("bat_cave","south");
}
