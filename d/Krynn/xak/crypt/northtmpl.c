/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

create_xak_room()
{
        set_short("The North Temple");
        set_long(BS(
           "You are standing in the north temple. The floor here is in a bad"
	 + " state and an old sewer pipe protrudes from the floor and leads"
	 + " down into further darkness below.", 70));

	add_exit(DDIR + "flourroom.c", "down", "@@down");
	add_exit(CDIR + "deadtmpl.c", "south", 0);

	add_item(({"pipe", "sewer pipe", "floor"}), "@@pipe");
	INSIDE
        DARK
}

pipe()
{
	write("The cataclysm seems to have forced the old sewer pipe up"
	 + " through the floor.\n");
	return "";
}

down()
{
	write(BS("You slide down the sewer pipe a long way before finally"
	 + " it empties out into another room. You land on a huge"
	 + " big bag full of flour which explodes and covers you and"
	 + " the whole room in a fine white powder.", 70));
	SAY(" jumps into the sewer pipe and slides down into the darkness.");
	return 0;
}
