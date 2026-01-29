inherit "/std/room";
#include "tunnel.h"
#include <macros.h>

reset_room()
{
}
 
create_room()
{
	set_noshow_obvious(1);

    set_short("End of tunnel");
	set_long(BSS("You find yourself at a dead end, with a small "+
		"hole over you, giving you a way to freedom. The "+
		"tunnel back south is dark, and you cannot see much.\n"));
 
    add_prop(ROOM_I_INSIDE, 1);

	add_exit(TUNN_D+"tunnel2","south",0);
	add_exit(SLUM_D+"hut4","up","@@exit_function@@");


	add_item(({"tunnels","tunnel"}),BSS(
			"These tunnels are so small you have to crawl "+
			"your way through. You suspect some small "+
			"creature have made them.\n"));
	add_item(({"hole","light hole"}),BSS(
			"The hole looks like it could give you a "+
			"passage out of this tunnel, but it might "+
			"crumble closed at any time.\n"));

}


exit_function()	{

	tell_room(environment(this_player()), QCTNAME(this_player()) + " leaves up.\n", this_player());
	write("You climb up through the hole, and you see the hole close\n"+
		"beneath you.\n");
	this_player()->move_living("M", SLUM_D+"hut4", 0);
	tell_room(environment(this_player()), QCTNAME(this_player()) + " arrives through a hole in the ground.\n", this_player());
	return 1;
}

