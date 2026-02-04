inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "volcano.h"

create_room()
{
    set_short("oon precipice.");
    set_long(BSN(
	"You are poised in windy insecutiry miles above the earth with " +
        "only space and death on one side and only slippery walls of " +
        "rocks on the other."
    ));

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VOLCANODIR + "precip02", "up", 0);
}


