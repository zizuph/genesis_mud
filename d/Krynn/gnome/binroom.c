inherit "/d/Krynn/std/room.c";

#include "/d/Krynn/common/defs.h"
#include "local.h"

object rub;

void
create_room()
{
	LIGHT;
	INSIDE;
	set_short("Inside some dustbin");
	set_long("This is a dead end of the corridors. The Gnomes "
		+ "are using this part of the caves "
		+ "to store the results of their less fortunate "
		+ "experiments.\n");
	
	add_exit(TDIR + "corridor1", "south", 0, 1);

	add_item("dust", "You are COVERED with it!\n");
	add_item("ground", "The ground is covered with rubbish of "
			+ "all sorts.\n");
	
	reset_room();
}

void
reset_room()
{
	if(!rub)
	{
		rub = clone_object(OBJ + "rubble.c");
		rub->move(TO);
	}
}

string area() {return "Inthecorridors";}
string wayout() {return "south";}
string tohelp() {return "south";}
string fromhelp() {return "south";}
