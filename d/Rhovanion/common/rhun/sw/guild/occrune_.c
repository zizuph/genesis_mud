inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"

init()
{
	::init();
	add_action("transfer","trace");
}

create_room()
{
	set_short("Rune chamber");
	set_long("This is a small, round chamber."
		+"  It is dim here, and oddly silent.  You feel the"
		+" presence of a dark power.  On the"
		+" north"
		+" wall, a large and complex rune is carved into the"
		+" dark stones.  Exits from this small, eerie room"
		+" lie to the"
		+" east, west and southeast."
		+"\n");
	
	add_exit(SWG+"hightrain","east",0);
	add_exit(SWG+"occspells","west",0);
	add_exit(SWG+"priv_chapel","southeast",0);
	
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE);
	
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
	add_item("rune","This large and intricately carved rune"
		+" immediately catches and holds your attention."
		+"  It consists of a single arch which"
		+" curves upward and then back down as it runs"
		+" from left to right."
		+"  You find yourself"
		+" reaching out to touch it, desiring to trace"
		+" your fingers along its shape, and to discover"
		+" what powers lie within."
		+"\n");
	
}

transfer(string str)
{
	if (!(str=="rune")) { write("Trace what?\n");}
	else
	{
		TP->catch_msg("You trace your fingers along the surface"
			+" of the rune, invoking it to magically transport you"
			+" to another place.\n");
		say(QCTNAME(TP)+" runs " + TPOS+" finger along"
			+" the surface of the rune,"
			+" and is suddenly gone!\n");
		TP->move_living("M",SWG + "occrune");
	}   
	return 1;
}

