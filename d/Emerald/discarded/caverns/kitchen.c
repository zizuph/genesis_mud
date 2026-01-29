/*
 * KITCHEN.c
 * This is the kitchen just south of the food hall in the Caverns
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   object door;

   set_short("Kitchen");
   set_long("    You find yourself in a mass of confusion. Pots are "+
	    "boiling over, skewers of meat and poultry are dripping "+
	    "grease and flaming up. Other pieces of meat are spitting "+
	    "and hissing as the flames scorch them. The floor is covered "+
	    "with slime and grease from split pots of mysterious "+
	    "concoctions. Raised to a safe level above all of the "+
	    "confusion is a walnut cask mounted up on the wall. Despite "+
	    "all of this, the most odd thing about this kitchen is "+
	    "that no effort has been taken to hide the water-dripping "+
	    "cave walls. All of the kitchen implements look terribly "+
	    "out of place next to the water and fungus-ridden black "+
	    "stone walls.\n\n");

   add_item(({"walnut cask","cask","mounted cask"}),
	    "The cask is marked with a skull and cross-bones. "+
	    "The odor from it reminds you of whiskey.  There is a cork "+
	    "hole in the bottom of it.  It appears to be empty.\n");
   
   add_item(({"poultry","meat","meats"}),
	    "The skewers of meat look great, even though they are "+
	    "a little burned.\n");

   add_item(({"slime","grease"}),
	    "The floors look like they've never been cleaned! The "+
	    "slime is probably from decayed food. Little puddles of grease "+
	    "reside in depressions in the slime.\n");

   add_item(({"pot","pots","concoctions","concoction"}),
	    "The pots are boiling over with wonderful smelling "+
	    "concoctions. The grease bubbling over the edges "+
	    "makes you doubt how good the food is, despite the "+
	    "great smell.\n");

   add_exit(THIS_DIR + "foodhall", "north");

   door=clone_object(THIS_DIR+"/obj/kitchen_door2");
   door->move(this_object());

}

