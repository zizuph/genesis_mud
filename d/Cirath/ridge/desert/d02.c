 /* The desert, just west of Tyr.
  * Dethraine, March 1998. Code (c) Damian Horton
  */

#pragma strict_types
#pragma save_binary

#include "defs.h"

inherit BASE_DESERT;

void
create_desert()
{
  set_short("In the outer agricultural fields surrounding Tyr.");
  set_long("On a dusty path amongst fields of crops controlled "+
	"by Tyr's nobles. Row upon row of slaves can be seen "+ 
	"tending to the fields, with armed overseers ensuring "+
	"that as much work as possible gets done. "+
	"The Ringing Mountains loom to the west, and north."); 

  add_item(({"slave","slaves"}),      
	"The slaves carefully weed the crops. Ruthless overseers "+
	"stand watch, ready to strike them for the slightest "+
	"lessening of their efforts. Those who dare to so much "+
	"as place their hands to their lips face a severe beating "+
	"or worse. Yet, it is their labour which allows the city-"+
	"state of Tyr to survive...\n");
  
  add_item(({"overseers","overseer"}),"Armed overseers are outnumbered "+
	"by slaves at most by a factor of 10:1. Any of them "+ 
	"who would be tempted to be of a kinder "+
	"heart realize that the only thing keeping them from "+
	"working the fields themselves is their ability to "+
	"discipline the mass of slaves.\n");

  add_item(({"crops","plants","crop","field","fields"}),
	"The fields are filled with some kind of bushes. Unripe "+
	"fruits clings to their scraggly branches. These are "+
	"bulis fruit are fermented in the production of "+
	"popular alcholic beverages.\n");

  add_item(({"mountains","Mountains","Ringing Mountains",
	"Ringing mountains","ringing mountains"}),
	"Stark and majestic, the Ringing mountains rise to the "+
	"west. To your north, one arc of the mountains also "+
	"towers skyward, while far to the southwest, you can "+
	"see another arc of the mountains jutting outwards into "+
	"the Athasian wastes.\n");

  add_cmd_item(({"food","crop","crops","fruit","fruits"}),
      ({"pick","take","harvest"}),"Taking the unripe bulis fruit "+
      "would accomplish nothing but angering entire fields full of "+
      "slaves and armed overseers.\n");

  add_exit(RIDGE_DESERT+"d03.c","east",0,6,0);
  add_exit(RIDGE_DESERT+"d01.c","west",0,6,0);
  add_exit(RIDGE_DESERT+"d06.c","southwest",0,6,0);
  add_exit(RIDGE_DESERT+"d07.c","south",0,6,0);
  add_exit(RIDGE_DESERT+"d08.c","southeast",0,6,0);
}


