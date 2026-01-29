//ROOM: Triel glade 5
// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include "defs.h"

// ROOM DEFINITION

void
create_room()
{

    set_short("central glade");
    set_long("You stand in a serene glade, the sound of running" +
        " water gurgles quietly all around you. Beams of sunlight" +
        " filter through the canopy of the trees looming above you." +
        " The area is thick with vegatation, making it feel rather" +
        " muggy. To your north you see a neatly groomed path of grey" +
        " shale leading you further into the glade; to the south is" +
	  " the underbrush from which you crawled through.\n");

    add_item(({"glade"}), "Dozens of colourful plants surround you, making" +
        " this a pleasurable retreat for the senses.\n");
    add_item(({"plants", "vegetation"}), "
    add_item(({"trees"}), " \n");

    add_exit(GLADE_ROOMS + "glade2", "west", 0);
    add_exit(GLADE_ROOMS + "glade6", "north", 0);

    }
