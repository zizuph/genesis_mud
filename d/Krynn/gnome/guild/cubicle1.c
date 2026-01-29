/* Created by Dajala
 * Cubicle in the main guild room
 * Enhances intelligence while in the room
 */

inherit "/d/Krynn/std/room";

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "../local.h"
#include "guild.h"

void
create_room()
{
	set_short("Inside a thinking cubicle");
	set_long("You are inside a thinking cubicle. Thoughts and ideas "
		+ "from all the other gnomes inside of cubicles rush into "
		+ "your brain. You suddenly have ideas you never thought "
		+ "about before. Thinking seems a lot more easy to you "
		+ "inside here! You even might be able to 'invent new "
		+ "modules'.\n");

	add_exit(GGUILD + "joinroom.c", "out", "@@int_down_again", 1);
	add_prop(ROOM_M_NO_TELEPORT, "You cannot concentrate with all "
		+ "these voices in your mind.\n");
	add_prop(ROOM_M_NO_MAGIC, "You cannot concentrate with all "
		+ "these voices in your mind.\n");
	INSIDE
}

void
init()
{
	::init();
	ADA("invent");
}

int
int_down_again()
{
	TP->set_stat_extra(3, (TP->query_stat_extra(3)) - 10); /* back to normal */
	"/d/Krynn/gnome/guild/joinroom.c"->one_more_free();
	return 0;
}

int
invent(string str)
{
	NF("Invent what?");
	if (str != "new modules")
		return 0;
	NF("Then you should join the guild!\n");
	if(!GMEMBER(TP))
		return 0;
	write("Even more thoughts rush over you. Images of new devices "
		+ "form before your spiritual eye. You feel an irresistable " 
		+ "urge to get to work at once before these fantastic ideas "
		+ "possibly vanish again.\nConcentrating on your purpose " 
		+ "you leave the cubicle and head for the planning "
		+ "chamber.\n");
	TP->command("out");
	TP->command("south");
	return 1;
}
