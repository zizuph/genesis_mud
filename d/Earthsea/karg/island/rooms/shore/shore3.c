#include <macros.h>
#include <stdproperties.h>
#include "../../std/defs.h"

inherit (ISL_DIR+"/std/room");

void
create_island_room()
{
	set_short("On the shore");
	set_long("You are standing on the sandy beach. "+
		"The waves come to you slowly with a soft"+
		" rumbling sound. To th south you notice a "+
		"small quiet bay. The shore spreads to the "+
		"north, to the east of you there is "+
		"a distant forest and beyond it you see some "+
		"mountains.\n\n");
	
	add_exit(SROOMS+"/docks","southeast");
	add_exit(SROOMS+"/shore2","north");
	add_exit(SROOMS+"/shore6","east");
	
	add_item("bay","To the south the shoreline gives in "+
		 "forming a small bay. You notice a primitive "+
		 "wooden pier at the east side of the bay.\n");
	add_item("pier","You can not make it out from here. "+
		 "Maybe you should come closer...\n");
		 
}
