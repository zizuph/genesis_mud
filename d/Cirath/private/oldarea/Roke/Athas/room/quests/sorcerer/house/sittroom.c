inherit "/std/room";

#include <stdproperties.h>
#include "/d/Roke/common/defs.h"
#include <macros.h>
 
create_room()
{
    set_noshow_obvious(1);
 
    set_short("Sitting room");
    set_long(BSS("This room serves both as a sitting room and as an entrance hall. "+
		"Here Templar Pandora receives her guests. There are some "+
		"chairs and tables here. There is a livingroom to the south, "+
		"a hallway to the east, while the exit is back west.\n"));

    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(HOUS_D+"hallway","east",0);
    add_exit(HOUS_D+"livingroom","south",0);
    add_exit(SOR_DIR+"garden","west","@@exit_function@@");

    add_item(({"chairs", "chair"}), BSS("The chairs are of a nice teak production, truly made by a real artist!\n"));
    add_item(({"tables", "table"}), BSS("The tables are made out of fine teak, and are in style with the chairs.\n"));

}

exit_function()	{

	tell_room(environment(this_player()), QCTNAME(this_player()) + " leaves through the door.\n", this_player());
	write("You leave through the front door.\n");
	this_player()->move_living("M", SOR_DIR+"garden", 0);
	tell_room(environment(this_player()), QCTNAME(this_player()) + " arrives through the door.\n", this_player());
	return 1;
}
