#include <macros.h>
#include <stdproperties.h>
#include "../../std/defs.h"

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
	
	add_exit(SROOMS+"/shore2","south");
	add_exit(SROOMS+"/rocks1","north","@@block");
	add_exit(SROOMS+"/shore4","east");
	
}

int block()
{
 write("Noting special there that worth your attention.\n");
 return 1;
}

