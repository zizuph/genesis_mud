/*
    Modified: 3 May 2003, by Bleys
        - fixed a typo
*/
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("inside cottage");
    set_long(
	"You enter the small cottage and step onto the polished flagstone " +
	"floor. The white walls are lined with polished pots and " +
	"kettles hanging on pegs. Dancing lights and shadows are cast " +
	"across the floor by the bright cozy fire in the fireplace.\n"
    );

    add_item(({"fireplace", "fire"}), 
	"The fireplace contains a brightly burning fire but there appears " +
	"to be nothing in the flames for them to feed upon!\n"
    );

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TOMBDIR + "cottage_front", "out", 0);
    add_exit(TOMBDIR + "cottage_sideroom", "east", 0);
    add_exit(TOMBDIR + "cottage_bookroom", "west", 0);
    add_exit(TOMBDIR + "cottage_kitchen", "north", 0);            
    
}


