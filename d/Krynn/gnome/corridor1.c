/* This room triggers and 'coordinates' the explosions in the other 
   corridor* - rooms and the explosroom. 
*/

inherit "/d/Krynn/std/room.c";

#include "/d/Krynn/common/defs.h"
#include "local.h"

int exp = 0;

void
create_room()
{
	LIGHT;
	INSIDE;
	set_short("A dusty corridor");
	set_long("This part of the caves seems to be a lot more dusty than "
		+ "the rest. There are iron tracks on the ground.\n");
	
	add_exit(TDIR + "toolroom.c", "west", 0, 1);
	add_exit(TDIR + "cavern7", "east" , 0,1);
	add_exit(TDIR + "binroom.c", "north", 0, 1);
	add_exit(TDIR + "corridor2.c", "south", 0, 1);

	add_item(({"tracks", "iron tracks"}) ,
		"They seem to be used quite often. They run from "
		+ "the south to the north branching off "
		+ "to the west.\n");
	add_item(({"dust", "ground", "walls"}), "");
	add_item("branch", "Then branch is set in a way that a wagon "
			+ "would run from north to south. There's a "
			+ "little square hole next to it, which you "
			+ "can possibly use to switch the branch provided "
			+ "you have a suitable tool.\n");
}

void
init()
{
	::init();
	if (!exp)
	{
		exp = 1;
		set_alarm(60.0, -1.0, "expl0_init");
	}
}

void
expl0_init()
{
	seteuid(getuid());
	"/d/Krynn/gnome/explosroom.c"->expl0();
	set_alarm(20.0, -1.0, "expl1_init");
}

void
expl1_init()
{
	seteuid(getuid());
	"/d/Krynn/gnome/corridor5.c"->expl1();
	"/d/Krynn/gnome/corridor4.c"->expl1();
	set_alarm(20.0, -1.0, "expl2_init");
}

void
expl2_init()
{
	seteuid(getuid());
	"/d/Krynn/gnome/corridor3.c"->expl1();
	"/d/Krynn/gnome/cave1.c"->exl1();
	set_alarm(20.0, -1.0, "expl3_init");
}

void
expl3_init()
{
	seteuid(getuid());
	"/d/Krynn/gnome/corridor2.c"->expl1();
	set_alarm(100.0, -1.0, "ready_again");
}

void
ready_again()
{
	exp = 0;
}


string area() {return "Inthecorridors";}
string wayout() {return "west east north south";}
string tohelp() {return "south";}
string fromhelp() {return "east north";}
