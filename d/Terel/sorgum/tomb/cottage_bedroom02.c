inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("cottage bedroom");
    set_long(
	"A small bedroom off of the kitchen.  The flagstone floor only " +
	"reaches part way into the room and the rest of the floor is " +
	"covered with shale tiles.  There is a small bed along one wall.\n"
    );

    add_item(({"bed", "small bed"}), 
	"The small bed is on a wooden frame.  The headboard is inscribed " +
	"with the initials T.A.\n"
    );

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TOMBDIR + "cottage_kitchen", "east", 0);
    
}


