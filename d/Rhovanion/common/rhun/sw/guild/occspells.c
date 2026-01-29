inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"

create_room()
{
	set_short("Occupational spells training room");
	set_long("You have entered the room where"
		+" the more advanced spells for occupation members of the"
		+" Spellweavers' guild are"
		+" taught.  The entire room is curved, being perfectly round,"
		+" and is formed of that same mysterious dark stone"
		+" that makes up the rest of this guild."
		+"  The dark walls are covered with hundreds of carved runes,"
		+" the meanings for many of which have been lost over time."
		+"  There will be other stuff here, but I don't know what right now."
		+"  Back to the east lies a small rune-chamber."
		+" \n");
	
	add_exit(SWG+"occrune_","east",0);
	
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE, 1);
	
	add_item(({"wall","walls","stone"}),"The walls of this"
		+" chamber are made of dark stone, and are polished"
		+" smooth.  You are unable to recognize the variety of"
		+" stone from which they wree made, centuries ago."
		+"  Hundreds of intricately-carved runes adorn the walls"
		+" here."
		+"\n");
	add_item("runes","Most of these runes are"
		+" indecipherable.  You can tell, however, that the stones"
		+" into which they were carved are many hundreds of years"
		+" old.\n");
	
}

