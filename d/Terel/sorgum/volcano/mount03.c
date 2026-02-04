inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "volcano.h"

create_room()
{
    set_short("on mountain.");
    set_long(BSN(
	"The soil becomes meagre with great patches of rock cropping out " +
	"and now and then the nest of a condor can be seen in a crevice"
    ));
    
    add_item(({"mountain"}), BSN(
	"The mountain towers silent and sinister."
    ));						      

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VOLCANODIR + "mount02", "down", 0);
    add_exit(VOLCANODIR + "mount04", "up", 0);
}


