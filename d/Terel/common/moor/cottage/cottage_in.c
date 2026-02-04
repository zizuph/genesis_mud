/*
    Modified: 3 May 2003, by Bleys
        - fixed a typo
*/
// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common/moor/cottage/
//    updated to Terel std room, etc

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

void
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

    add_exit("cottage_front", "out", 0);
    add_exit("cottage_sideroom", "east", 0);
    add_exit("cottage_bookroom", "west", 0);
    add_exit("cottage_kitchen", "north", 0);            
    
}


