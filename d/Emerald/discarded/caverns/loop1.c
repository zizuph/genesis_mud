/*
 * LOOP1.c
 * Looping Tunnel, Caverns
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   set_short("Curving Tunnel");
   set_long("   You are in a curving tunnel. It curves sharply around "+
	    "to the northwest and to the west of here. The sharp curve "+
	    "manages to blot out most of the light coming from the "+
	    "large cave to the west. The sound of water dripping echoes "+
	    "throughout the entire tunnel, disguising the true location "+
	    "of the drips.\n");

   add_prop(ROOM_I_LIGHT, 0);

   add_item(({"cave", "large cave", "west"}),
	    "You can't make out much of the large cave to the west "+
	    "from here, however, you can tell that there is a rather "+
	    "large source of light there, most likely a torch.\n");
   
   add_exit(THIS_DIR + "main5", "west");
   add_exit(THIS_DIR + "loop2", "northeast");

}

