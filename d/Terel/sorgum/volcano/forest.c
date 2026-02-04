inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "volcano.h"

create_room()
{
    set_short("forest.");
    set_long(BSN(
	"The vast oaks thin out somewhat, standing quite dead or dying " +
        "among the unnaturally dense fungi and rotting mold and mushy "
        "logs of their fallen brothers."
    ));
    
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "hill_base", "east", 0);
    add_exit(TOMBDIR + "cottage_in", "enter", 0);
}


     
