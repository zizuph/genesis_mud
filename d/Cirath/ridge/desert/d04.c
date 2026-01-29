 /* The desert, just west of Tyr.
  * Dethraine, March, 1998. Code (c) Damian Horton.
  */

#pragma strict_types
#pragma save_binary

#include "defs.h"

inherit BASE_DESERT;

void
create_desert()
{
  set_short("Amidst the slave driven farmlands of Tyr.");
  set_long("On a dusty path amongst fields of scorched "+
	"crops. Row upon row of slaves work endlessly, "+
	"tending the fields, while armed overseers ensure that "+
	"they work as hard as they can. It is their labour on "+
	"the nobles estates which feeds the populace of Tyr. "+ 
	"Bounding the orchard to the east are the walls of that "+
	"great city.\n");

  add_item(({"slaves","slave"}),
	"The life of a field working slave in "+
	"Athas is a brief and tortured one. Given only the "+
	"minimum amount of food and water necessary to survive, "+
	"they pour their efforts into the parched landscape, "+
	"in the hopes that it will yield enough food for "+
	"them as well as their overlords. Ruthless overseers "+
	"stand watch, ready to strike them for the slightest "+
	"lessening of their efforts.\n"); 
	
  add_item(({"overseers"}),"Armed overseers are outnumbered "+
	"by slaves at most by a factor of 10:1. Any of them "+ 
	"who would be tempted to be of a kinder "+
	"heart realize that the only thing keeping them from "+
	"working the fields themselves is their ability to "+
	"discipline the mass of slaves.\n");

  add_item(({"crops","plants","crop","field","fields"}),
      "The fields are filled with a low-growing plant, whose yellow "+
      "leaves spread out in a fan-shaped formation. It is Olacea, "+
      "a staple vegetable grown in Athas. Its leaves are often "+
      "served raw, as a salad, but can also be cooked.\n");

  add_item(({"walls","city walls"}),"Immense stone walls, tens of "+
	"feet in thickness serve to isolate Tyr from the harsh wilderness "+
	"of Athas. It would take a truly amazing force to break through "+
	"those walls.\n");

  add_cmd_item(({"walls", "city walls"}),({"climb","climb up"}), 
      "Not bloody likely!\n");

  add_cmd_item(({"food","crop","crops","olacea","leaves"}),
      ({"pick","take","harvest"}),"You dare not pick the crops, for that "+
      "would anger entire fields full of workers and armed overseers.\n");

  add_exit(RIDGE_DESERT+"d03.c","west",0,6,0);
  add_exit(RIDGE_DESERT+"d08.c","southwest",0,9,0);
  add_exit(RIDGE_DESERT+"d09.c","south",0,6,0);
}


