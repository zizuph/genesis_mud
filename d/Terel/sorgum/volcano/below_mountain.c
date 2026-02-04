inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "volcano.h"

create_room()
{
    set_short("below mountain.");
    set_long(BSN(
	"The ground slopes upward to the foot of the mountain thinly " +
	"covered with scrub oaks and ash trees and strewn with bits of " +
        "rock, lava and ancient cinder."
    ));
    
    add_item(({"mountain"}), BSN(
	"The mountain towers silent and sinister."
    ));

    add_item(({"oaks", "tree", "trees"}), "The trees look scrubby\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VOLCANODIR + "hill_base", "east", 0);
}
