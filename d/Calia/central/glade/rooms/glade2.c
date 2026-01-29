//ROOM: Triel glade 2

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include "defs.h"

// ROOM DEFINITION

void
create_room()
{

    set_short("central glade");
    set_long("You are standing on a grey shale path in the midst" +
        " of a warm glade. The shale path continues in an east/west" +
	  " direction, and you can see a faint, rugged trail leading off" +
	  " to the north towards a rockface. To the northeast, sunlight is" +
	  " illuminating a deep-looking pool of water. All around you birds" +
	  " are chirping and fluttering about the trees.\n"
 
    add_item(({"glade"}), "Dozens of colourful plants surround you, making" +
        " this a pleasurable retreat for the senses.\n");
    add_item(({"birds"}), "
    add_item(({"rockface"}), "From what you can see through the dense foliage" +
	  " of trees and bushes, it appears to be your standard, run-of-the-mill" +
	  " rockface. A closer examination might reveal more.\n");
    add_item(({"trail"})), "There is a faint trail formed from plants that" +
 	  " have been trampled down for some reason.\n");

    add_exit(GLADE_ROOMS + "glade3", "west", 0);
    add_exit(GLADE_ROOMS + "glade5", "east", 0);
    add_exit(GLADE_ROOMS + "glade1", "south", 0);
    add_exit(GLADE_ROOMS + "glade7", "trail", 0);


}
