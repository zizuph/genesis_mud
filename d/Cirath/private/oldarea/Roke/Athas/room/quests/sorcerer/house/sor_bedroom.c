inherit "/std/room";
#include <stdproperties.h>
#include "/d/Roke/common/defs.h"

create_room()
{
 
    set_short("Bedroom");
    set_long(BSS("This is the templar Pandoras's bedroom, there is a large bed here. You may go down to "+
		"the library again, or you may go up to the laboratory.\n"));

    add_prop(ROOM_I_INSIDE, 1);
 
	add_exit(HOUS_D+"stair2","down",0);
	add_exit(HOUS_D+"stair3","up",0);

    add_item(({"large bed", "bed"}), BSS("The bed look large and comfortable, but you do not dare to lie down in a templars bed.\n"));
 
}
