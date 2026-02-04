inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "volcano.h"

create_room()
{
    set_short("under ledge.");
    set_long(BSN(
	"To the left a precipice drops straight down from unknown " +
        "heights to unknown depths, with a cave's dark mouth just " +
        "out of reach above you."
    ));
    
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VOLCANODIR + "precip01", "east", 0);
}


