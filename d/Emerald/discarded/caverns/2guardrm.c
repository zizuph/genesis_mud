/*
 * 2GUARDRM.c
 * Guard Room outside the Jail in the caverns
 * - Alaron September 13, 1996
 */

#include "defs.h"
#include <stdproperties.h>

inherit BASECAVE;

void
create_cave()
{
   object door;

   set_short("North Guardroom");
   set_long("   This cave is more well lit than the rest of the chambers "+
	    "and tunnels surrounding it. There are several covered lamps "+
	    "hanging from iron pitons which have been hammered into the "+
	    "cold, wet stone walls. It appears that this is a guard "+
	    "room of some kind. There is a heavy iron door built into "+
	    "the stone to the northeast. The foul stench which assaulted "+
	    "your senses to the west is now several times more potent, "+
	    "threatening to make your eyes water.\n\n");
   
   
   add_exit(THIS_DIR + "main12", "west");
   add_exit(THIS_DIR + "main11", "southwest");
   add_exit(THIS_DIR + "2jail", "northeast");
        
   seteuid(geteuid());
   door = clone_object(THIS_DIR+"obj/pdoor5a");
   door ->move(TO);

}

