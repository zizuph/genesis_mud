inherit "/std/room";
#include <stdproperties.h>
#include "/d/Roke/common/defs.h"
 
create_room()
{
	set_noshow_obvious(1);

     set_short("Guest room");
	set_long(BSS("This is a small bedroom, used as a guest room. "+
		"There is a small bed here, and there is a little window "+
		"on the northern wall, giving the room some light.\n"));


    add_prop(ROOM_I_INSIDE, 1);

	add_exit(HOUS_D+"hallway","south",0);

	add_item(({"bed","small bed"}), BSS(
		"This is a small, cosy bed, not unlike the other beds you "+
		"have seen. The bed is clead with white sheats, and there "+
		"is a small pillow in one end.\n"));

	add_item(({"pillow","small pillow"}), BSS(
		"This is a small pillow, didn't you understand that ?\n"));

	add_item(({"window","little window"}), BSS(
		"As you look through the window, you understand how the "+
		"room is ligted. High up, shining directly on the window, "+
		"the sun is standing bright. Outside the window you see "+
		"some parts of the garden, but you cannot see far.\n"));
}
