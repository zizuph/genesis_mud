#include "../../std/defs.h"
#include <macros.h>
#include <stdproperties.h>

inherit ISL_DIR+"/std/room";

void
create_island_room()
{
	set_short("On the shore");
	set_long("You are standing on the sandy beach. "+
		"The waves come to you slowly with a soft"+
		" rumbling sound. The shore spreads to the "+
		"north and the south, ahead of you there is "+
		"a distant forest and beyond it you see some "+
		"mountains.\n\n");
	
	add_exit(SROOMS+"/shore3","south");
	add_exit(SROOMS+"/shore1","north");
	add_exit(SROOMS+"/shore5","east");
	
}