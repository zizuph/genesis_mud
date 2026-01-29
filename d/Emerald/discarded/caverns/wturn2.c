/*
 * WTURN2.c
 * West Turn in the Tunnels
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   set_short("Tunnel Passage");
   set_long("   The tunnel widens a bit to the southeast and narrows "+
	    "slightly as it continues west where the tunnel takes a "+
	    "very sharp turn. The shadows created by the turn prevent "+
	    "you from seeing anything detailed in that direction. The "+
	    "powerful smell of the fungus which inhabits the walls "+
	    "of this cave system is prevalent here, as is the echoing "+
	    "noise of the water which incessantly drips from the "+
	    "ceiling.\n\n");

   add_item( ({"turn", "sharp turn", "corner", "west"}),
	     "You can't make out very much detail of that "+
	     "corner from here.\n");

   add_exit(THIS_DIR + "wturn3", "west");
   add_exit(THIS_DIR + "wturn1", "southeast");

}
