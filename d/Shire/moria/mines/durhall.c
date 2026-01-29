#include "defs.h"

CONSTRUCT_ROOM {
    set_short("King Durin's Throne Hall");
    set_long("King Durin's Throne Hall!\nIt is said that the King of the "+
	     "Mountains used to keep his court here, before the trolls took "+
	     "over almost all parts of Moria, and made it uninhabitable for "+
	     "dwarfs and humans. By the western wall there still is standing "+
	     "the grand throne of the King, but noone is ever here. To the "+
	     "south is a portal to a smaller room, and to the east a wide "+
	     "passage.\n");
    add_item("throne",
	"It is not here, it is further west.");
    add_item(({"portal","passage","smaller room"}),
	"Perhaps go there to find out?");
    EXIT("crosroad","east");
    EXIT("guestroom","south");
    EXIT("throne","west");
}
