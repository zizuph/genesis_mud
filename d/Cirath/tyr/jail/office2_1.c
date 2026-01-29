/*
* Created by: Luther
* Date: 11 August 2001
*
* File: /d/Cirath/tyr/jail/office2_1.c
* Comments: Unused office in Tyr's Jail, Office has no light aswell.
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 0);
	set_short("office");
	set_long("This is the office in charge of maintenace in the jail. "
		+"Cobwebs and dust cover everything due to the lack of use. "
		+"You can make out a tapestry on the wall and there is a desk "
		+"in the corner. The torches on the walls look like they "
		+"haven't been used in years.\n");

	add_item("tapestry", "This is a small tapestry, only 3 feet wide, and "
		+"covered in dust. You think you might be able to clean it, "
		+"but giving the thickness of the dust your not sure thats "
		+"posible.\n");

	add_item(({"torch", "torches"}), "The torches look like they haven't "
		+"been used in years, and they seem to be decaying.\n");

	add_item("desk", "Upon examining the desk you notice some very old "
		+"writing implements and behind the desk is a rotten chair.\n");

	add_cmd_item("tapestry", "clean", "You start to beat on the tapestry "
		+"hoping to clean it, and cover yourself in dust. The tapestry "
		+" is still covered in dust but you think you can make out a "
		+" warrior dressed in athasian armours wielding a ancient axe.\n"); 

	add_cmd_item(({"torches", "torch"}), "light", "You try to light a torch "
		+"but it decays and falls to the floor.\n");

	add_exit(TYR_JAIL + "jail2_7.c", "east", 0,1);
	reset_room();
}
