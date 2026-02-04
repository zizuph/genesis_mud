inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "volcano.h"

create_room()
{
    set_short("near mountain.");
    set_long(BSN(
	"The gaunt side of the mountain looms higher as you approach it.  " +
	"There are sparse trees on lower slopes and feeble shrubs above " +
        "them and then the bare hideous	rock rises into the sky to mix with " +
	"frost and ice and eternal snow."

    ));
    
    add_item(({"stone", "rock"}), BSN(
	"The sombre stone is rugged in places are solid streams of lava " +
	"and scoraic heaps that litter the slopes and ledges."
    ));						      

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "below_mopuntain", "north", 0);
    add_exit(TOMBDIR + "forest", "west", 0);
}


