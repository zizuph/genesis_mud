/*
 * WTURN1.c
 * Western Turn inthe Caverns
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   set_short("Southwest Passageway");
   set_long("   The passageway curves to the northwest and to the "+
	    "east. The foul stench of the fungus which seems to live "+
	    "on the walls of this cavern system fills the air. Peering "+
	    "through the dim light to the east, you can see the "+
	    "passage widening into a large intersection. The air "+
	    "here is still and moist. After looking around the area, "+
	    "you stop a moment to wonder just where the light is "+
	    "coming from. There are cracks and holes in the caves "+
	    "everywhere, and it seems that in very convenient places, "+
	    "some of these cracks are eminating light.\n\n");

   add_item( ({"cracks", "holes", "light"}),
	     "There are cracks and holes all over the caverns, but it "+
	     "seems to you that in places where the darkness begins to "+
	     "become inhibiting, there is a conveniently located crack "+
	     "or hole in the wall which is allowing some light from "+
	     "an unknown source to filter through. That makes you wonder "+
	     "about the true nature of these caves.\n");


   add_exit(THIS_DIR + "wturn2", "northwest");
   add_exit(THIS_DIR + "main4", "east");

}
