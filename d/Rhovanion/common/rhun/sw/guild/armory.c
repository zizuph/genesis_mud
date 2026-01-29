inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
#include "sw.h"

create_room()
{
	set_short("Armory");
	set_long("This small, square room is where the"
		+" Spellweavers keep a few of those mundane objects which"
		+" they are forced to lower themselves to using.  Members"
		+" are highly encouraged to drop anything useful here, and"
		+" are welcomed to take whatever they may require.  Back to"
		+" the east of this room lies a small private chapel."
		+"\n");
	
	add_exit(SWG + "priv_chapel","east",0);
	
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE, 1);
	
	add_item(({"wall","walls","stone"}), "The walls of this"
		+" chamber are made of dark stone, and are polished"
		+" smooth.  You are unable to recognize the variety of"
		+" stone from which they were made, centuries ago.\n");
	add_item(({"corner","corners"}),"Peering into the corners of"
		+" this shadowy chamber, you can see nothing; yet you are unable to"
		+" shake the feeling that some dark force watches over you, and over"
		+" this place.\n");
	
	SGT
	clone_object(SWG + "sw_knife")->move(TO);
	SGT
	clone_object(SWG + "sw_knife")->move(TO);
	SGT
	clone_object(SWG+"sw_lthr")->move(TO);
	
}

