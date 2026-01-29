inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
#include "sw.h"

init()
{
	::init();
	add_action("transfer","trace");
}

create_room()
{
	set_short("Departure chamber");
	set_long("There is no way of knowing for sure,"
		+" but somehow you sense that this chamber is the departure"
		+" point from the guild of the Spellweavers.  The room is roughly"
		+" square, hewn of the strange, dark, and unidentifiable"
		+" stone as the rest of this place.  The heavy feeling of"
		+" some omnipresent power hangs in the air here, making"
		+" strangers of the guild rather uncomfortable."
		+"  There are two runes carves into the rock of the eastern"
		+" wall here that you might want to examine.  You"
		+" can also exit this room by heading off to the north,"
		+" south, northwest or southwest."
		+"\n");
	
	add_exit(SWG+"pub_board","north",0);
	add_exit(SWG+"layspells","south",0);
	add_exit(SWG+"strune","northwest",0);
	add_exit(SWG+"occrune","southwest",0);
	
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE,1);
	
	add_item(({"wall","walls","stone"}),"The walls of this"
		+" chamber are made of dark stone, and are polished"
		+" smooth.  You are unable to recognize the variety of"
		+" stone from which they were made, centuries ago."
		+"  On one wall is carved a large, intricate"
		+" rune; perhaps you should examine it more closely."
		+"\n");
	add_item(({"corner","corners"}),"Peering into the corners of"
		+" this shadowy chamber, you can see nothing; yet you are unable to"
		+" shake the feeling that some dark force watches over you, and over"
		+" this place.\n");
	add_item("rune","There are two runes here on the east wall.  Which would you"
		+" like to look at, the left or the right?\n");
	add_item("runes","Two carved runes adorn the eastern"
		+" wall of this room, a left and a right.  Perhaps you can examine each"
		+" individually?\n");
	add_item(({"right","right rune"}),"The right rune"
		+" is apparently only to be used by members of this guild.  It"
		+" is quite intricate, including a circle with several lines"
		+" pointing off at odd angles.\n");
	add_item(({"left","left rune"}),"The rune on the"
		+" left is a simple shape.  You have the feeling that this is the"
		+" rune non-members might take in leaving the guild.\n");
	
}

transfer(string str)
{
	if (str=="rune")
	{
		write("Trace which rune? The right or the left?\n");
		return 1;
	}
	if (str=="runes")
	{
		write("You may only trace one rune at a time, the right or the left.\n");
		return 1;
	}
	if ((str=="right")||(str=="right rune"))
	{
		if (!(TP->query_guild_member("Spellweavers")))
		{
			write("You trace your fingers"
			+" along the surface of the rune,"
			+" but nothing happens.\n");
		}
		else
		{
			say(QCTNAME(TP)+" runs "
			+TP->query_possessive()+" finger along"
			+" the surface of the rune,\n"
			+" and is suddenly gone!\n");
			TP->move_living("","/d/Rhovanion/gunther"+"workroom");
		/* ^^^^^^^^ should go to some helpful location for members (in town?)*/
		}
	}
	else
	{ /* Only option left is left rune*/
		write("You trace your fingers"
		+" along the surface of the rune, and"
		+" feel yourself magically moved"
		+" to another location.\n");
		TP->move_living("",ME+"workroom");
		/* ^^^^^^^^^^^^ should go to level 5 of castle */
	}
	return 1;
}

