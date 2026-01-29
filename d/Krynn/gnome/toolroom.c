inherit "/d/Krynn/std/room.c";

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>

object aro1;

void
create_room()
{
	set_short("The Gnomish Toolstore");
	set_long("This is the Gnomes' Toolstore. Here they can get the "
		+ "necessary equipment for their important experiments. "
		+ "The room is divided into two halves by a large counter. Along "
		+ "the walls in the rear part of the room you see well stocked "
		+ "shelves. To the wall near the entrance somebody "
		+ "nailed a sign. There are iron tracks on the ground.\n");

	add_item(({"tracks", "iron tracks"}) ,
		"They seem to be used quite often. They come from the east and "
		+ "end in front of the counter.\n");
	add_item(("sign"), "There are words written on it!\n");
	add_item(("tools"), 
		"There are hundreds of them neatly arrayed on shelves "
		+ "along the walls. In front of each you see a small "
		+ "label.\n");
	add_item(("shelves"), "The shelves stand along the walls. Hundreds of "
			+ "tools are stored there.\n");
	add_item(({"counter", "desk"}), "It is wooden.\n");
	add_item(({"label", "labels"}), "They are quite small.\n");

	LIGHT;
	INSIDE;

	add_exit(TDIR + "corridor1", "east", 0); 

	reset_room();

}

void
init()
{
	::init();
	ADA("read");
	ADA("borrow");    /*waiting for quests or NPC's to borrow tools.*/
}

int
read(string str)
{
	NF("Read what?\n");
	if (str != "sign") 
		return 0;
	write("Welcome to my toolstore. You can borrow tools "
		+ "from me if you have been authorized to do so "
		+ "by your superior. Or you could just hand me "
		+ "your list.\nAron, the Toolmaster.\n");
	return 1;
}

int
borrow(string str)
{
    object toolmaster = present("aron", TO);
	if (!toolmaster)
	{
		write("The toolmaster isn't here to lend you anything.\n");
		return 1;
	}
	NF("Borrow what? Tools?\n");
	if (str != "tools")
		return 0;
    toolmaster->command("say IAmSorry,YouHaveNotBeenAuthorized"
		+ "ToBorrowTools.");
	return 1;
}

void
reset_room()
{
	if (!aro1)
	{
		seteuid(getuid(TO));
		aro1 = clone_object(MON + "aron.c");
		aro1->move_living("xxx", TO);
	}
}

string area() {return "Inthetoolshop";}
string wayout() {return "east";}
string tohelp() {return "east";}
string fromhelp() {return "east";}
