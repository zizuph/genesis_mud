/*
 * 6jail.c
 * This is a hallway through the prison in the caverns.
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
  object guard;
  
  set_short("Cavernous Passageway");
  set_long("   You are standing in a winding, tube-like cavern. It "+
	   "vaguely resembles a hallway in the sole aspect that "+
	   "there are doors branching out from the natural cave "+
	   "walls. The doors are thick, heavy doors with iron bars "+
	   "on them, much like those used in some prisons. The soft, "+
	   "trickling sound of moisture running down through cracks "+
	   "and channels in the rock walls echoes throughout the "+
	   "cavern.\n\n");

  add_prop(ROOM_I_INSIDE, 1);
  add_prop(ROOM_I_LIGHT, 0);

  add_item( ({"doors", "prison doors", "heavy doors", "iron bar doors",
		"bars", "iron bars"}),
	    "Peering through the cavern to the northeast and south, "+
	    "you notice a few heavy, iron-barred doors recessed into "+
	    "the cave wall itself, as if the cells had been carved out of "+
	    "the cave and the doors added afterward.\n");
  
   add_exit(THIS_DIR + "5jail", "northeast");
   add_exit(THIS_DIR + "7jail", "south");
  
}
