#include "defs.h"

CONSTRUCT_ROOM {
    set_short("This is a small cave filled with soil and pebbles.");
    set_long("This is a small cave filled with soil and pebbles. "+
	     "Unfortunately the only exit is south.\n");
    EXIT("bat_cave","south");
}
