inherit "/std/room";
#include <stdproperties.h>
#include "/d/Roke/common/defs.h"

create_room()
{
	set_noshow_obvious(1);
 
    set_short("Kitchen");
    set_long(BSS("This is the templar Pandora's kitchen, here a maid works "+
	     "with prepearing food for her mistress and her friends. "+
	     "There is a kitchen sink here. The exit is back west.\n"));

    add_prop(ROOM_I_INSIDE, 1);

	add_exit(HOUS_D+"hallway","west",0);

    add_item(({"sink", "sink"}), BSS("The sink looks like it's just polished.\n"));

}
