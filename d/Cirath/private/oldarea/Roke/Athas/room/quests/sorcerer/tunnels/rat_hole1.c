inherit "/std/room";
#include "tunnel.h"

reset_room()
{
}
 
create_room()
{
    object key;
	set_noshow_obvious(1);

    set_short("Small tunnel");
	set_long(BSS("You find yourself in a small tunnel, and you "+
		"suspect that it can have been made by rats. There "+
		"is a small hole to your east, and a narrow tunnel "+
		"leading north.\n"));
 
    add_prop(ROOM_I_INSIDE, 1);

	add_exit(CELL_D+"cell1","east",0);
	add_exit(TUNN_D+"rat_hole2","north",0);

	clone_object(A_NPC_D+"rat")->move_living(" arrives.", this_object());

	add_item(({"tunnels","tunnel"}),BSS(
			"These tunnels are so small you have to crawl "+
			"your way through. You suspect some small "+
			"creature have made them.\n"));
	add_item(({"hole","rat hole"}),BSS(
			"The hole is just big enough to fit a rat.\n"));

}
