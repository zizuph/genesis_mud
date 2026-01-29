inherit "/d/Krynn/std/room.c";
#include "/d/Krynn/common/defs.h"
#include "local.h"

void
create_room()
{
	LIGHT;
	INSIDE;
	set_short("A really dusty and smoky corridor");
	set_long("There is dust and smoke all over the place. To the southwest a "
		+ "wall broke down opening a small entrance into a room from where you "
		+ "can hear strange noises. Also the origin of the smoke seems to be "
		+ "there. The walls and ceiling are covered with cracks. This tunnel might "
		+ "cave in any minute. You see something on the ground, gleaming through "
		+ "the smoke.\n");
	
	add_exit(TDIR + "corridor5", "west", 0, 1);
	add_exit(TDIR + "corridor3", "east", 0, 1);
	add_exit(TDIR + "explosroom", "southwest", "@@myexit", 10);

	add_item(({"tracks", "iron tracks"}), "They run from the west to the east.\n");
	add_item("dust", "You are COVERED with it!\n");
	add_item("ground", "You cannot see it well because it is covered by smoke. But "
			+ "there seem to be tracks on the ground.\n");
	add_item(({"walls","cracks"}), "There are cracks in the walls and ceiling "
				+ "all over this place. You do not feel safe at all"
				+ "in here.\n");
	add_item(({"smoke", "clouds"}),	"This is the sort of smoke you do not like. "
				+ "It is black, thick, oily and stays close to the "
				+ "ground.\n");
}

void
expl1()
{
	tell_room(TO,
		"You hear some strange humming noises coming from "
		+ "the southwest.\n");
	set_alarm(20.0, -1.0, "expl2");
}

void
expl2()
{
	tell_room(TO,
		"The humming increases into a load rumbling and "
		+ "rattling.\n");
	set_alarm(20.0, -1.0, "expl3");
}

void
expl3()
{
	tell_room(TO, "Now also the very ground you are standing on is shaking "
		+ "fiercly! You can barely remain standing!\n");
	set_alarm(20.0, -1.0, "expl4");
}

void
expl4()
{
	tell_room(TO, "Suddenly there's a terrifying explosion in the room to "
		+ "the south. The walls start to shake, dust and "
		+ "small stones are raining onto you from the ceiling! "
		+ "Thick clouds of smoke sweep into the room and "
		+ "you cannot see anything anymore.\n");
	add_prop(ROOM_I_LIGHT, -10);
	set_alarm(20.0, -1.0, "expl5");
}

void
expl5()
{
	tell_room(TO,
		"As suddenly as everything started it becomes "
		+ "quiet again.\nReally deadly quiet!\n");
	set_alarm(30.0, -1.0, "smokegone");
}

void
smokegone()
{
	tell_room(TO, "The smoke seems to have settled down again.\n");
	add_prop(ROOM_I_LIGHT, 1);
}

int
myexit()
{
	write("You climb over the rubble and squeeze through the opening.\n");
	return 0;
}

string area() {return "Inthecorridors";}
string wayout() {return "west east southwest";}
string tohelp() {return "west";}
string fromhelp() {return "east";}
