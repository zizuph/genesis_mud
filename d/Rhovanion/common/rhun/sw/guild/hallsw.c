inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"

create_room()
{
	set_short("Dark hallway");
	set_long("This dark hallway turns here,"
		+" heading off into shadow to the east and north."
		+"  There is a chill in the air, yet it is not cold."
		+"  You notice the strange texture of the walls here,"
		+" and wonder what material these stones might be made"
		+" of.\n");
	
	add_exit(SWG+"arrive","north",0);
	add_exit(SWG+"trrune","east",0);
	
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE,1);
	
	add_item(({"wall","walls","stone"}),"The walls of this"
		+" chamber are made of dark stone, and are polished"
		+" smooth.  You are unable to recognize the variety of"
		+" stone from which they were made, centuries ago.\n");
	add_item(({"corner","corners"}),"Peering into the corners of"
		+" this shadowy chamber, you can see nothing; yet you are unable to"
		+" shake the feeling that some dark force watches over you, and over"
		+" this place.\n");
}

