/*
 * LOOP2.c
 * Bending Tunnel
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   set_short("Tunnel");
   set_long("   You have come to a narrow bend in the tunnel. Around "+
	    "the bend in either direction to the northwest or southwest "+
	    "you can see the faint but unmistakable glow of torchlight. "+
	    "However, that light is prevented from reaching this corner "+
	    "by the bends in the jagged, rock walls. You are overwhelmed "+
	    "by the foul odor that seems to be eminating from an ugly "+
	    "fungus growing on the damp walls. The walls here appear "+
	    "to be somehow more natural than the rest of the "+
	    "caverns, as if this area was never touched by a chisel "+
	    "or hammer.\n\n");

   add_prop(ROOM_I_LIGHT, 0);


   add_exit(THIS_DIR + "loop1", "southwest");
   add_exit(THIS_DIR + "loop3", "northwest");
   

}
