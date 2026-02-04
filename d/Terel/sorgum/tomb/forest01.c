inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("forest.");
    set_long(
	"You have left the path and ventured into the forest.  The trees " +
	"are rather thick here but they appear to thin out a bit to the " +
        "north.  Thick shrubbery and vegetation grow among the trees and " +
	"moss grows on the stones buried among the leaves and pine " +
	"needles of the forest floor.\n"
    );

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "thicket", "west", 0);
    add_exit(TOMBDIR + "clearing", "northwest", 0);
    add_exit(TOMBDIR + "path02", "south", 0);        
}


