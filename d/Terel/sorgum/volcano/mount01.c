inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "volcano.h"

create_room()
{
    set_short("on mountain.");
    set_long(BSN(
	"The slope becomes precipitous and rather dizzying as you push " +
	"on through the grass where anemic shrubs grow here and there.  " +
        "You feel as if might be dangerous to proceed."
    ));
    
    add_item(({"mountain"}), BSN(
	"The mountain towers silent and sinister."
    ));						      

    add_item(({"shrub", "shrubs"}), BSN(
       "The shrubs look quite unhealthy.  Mostly bare branches " +
       "have sparse patches of browning leaves clinging to them."
    ));
    
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VOLCANODIR + "mount01", "up", 0);
    add_exit(VOLCANODIR + "below_mountain", "down", 0);    
}


