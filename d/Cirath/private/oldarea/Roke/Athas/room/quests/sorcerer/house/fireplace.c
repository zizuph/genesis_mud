inherit "/std/room";

#include <stdproperties.h>
#include "/d/Roke/common/defs.h"

reset_room()
{
}
 
create_room()
{
 
    set_short("Fireplace");
	set_long(BSS("You are standing on the inside of a large fireplace "+
		"containing nothing but ashes. Maybe you should consider "+
		"get out of here, and get some air that is a bit fresher.\n"));

    add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 0);
 
	add_exit(HOUS_D+"livingroom","out",0);

	add_item("fireplace", BSS(
		"You are inside the fireplace, not much to see exept "+
		"ashes.\n"));

	add_item(({"ash","ashes"}), BSS(
		"You notice that one of the coal pieces is larger than the "+
		"rest of the ashes and dirt.\n"));

	add_item(({"coal","coal piecepiceg"}), BSS(
		"The coal piece have the destinguish look of a torch, but "+
		"you don't think it really is a torch, since it is totally "+
		"burned, very unlike a torch.\n"));
 
    call_out("reset_room", 1);
}
