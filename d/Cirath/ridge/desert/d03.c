 /* Agricultural fields, just west of Tyr.
  * Code (c) Dethraine, February 1998.
  */

#pragma strict_types
#pragma save_binary

#include "defs.h"

inherit BASE_DESERT;

void
create_desert()
{
  set_short("Amidst the slave driven farmlands of Tyr.");
  set_long("On a dusty path in an orchard of tree-like cacti. "+
      "Hundreds of slaves toil endlessly, picking baskets full "+
      "of broad needles from the cacti. Armed overseers stand "+
      "at the ready, in the event that any slave should work "+
      "to less than his or her full capacity.\n");

  add_item(({"slaves","slave"}),"Slavery does not discriminate "+
      "based upon race in the harsh environment of Athas. Humans, "+
      "muls, dwarves, and even the occasional halfling or elf "+
      "can all be seen toiling under the brutal heat of Athas's sun. "+
      "Armed overseers ensure that the slaves work to "+
      "their fullest capacity.\n");

  add_item(({"overseers","overseer"}),"Armed overseers are outnumbered "+
     "by slaves at most by a factor of 10:1. Like the slaves, "+
     "they are of varied race, but are invariably strong, and "+
     "are typically of a cruel and ruthless disposition. "+
     "They employ whips and cudgels to good effect, but one "+
     "notices that many an obsidian blade can also be found, "+
     "in their possession, for they must also protect against "+     
     "raiders, rampaging beasts, and wholescale insurrection.\n");

 add_item(({"crops","plants","crop","field","fields","plant",
     "tree","trees","cactus","cacti"}),
     "The needles from Faro trees are ground to produce a fine flour "+  
     "from which most Athasian breads and cakes are derived. "+
     "The plant also infrequently produces a tasty and highly "+
     "valued fruit, but it is the needles which are presently "+    
     "being harvested by swarms of exhausted slaves.\n");

  add_cmd_item(({"food","crop","crops","needles","tree","cacti","trees"}),
      ({"pick","take","harvest"}),"You dare not pick the crops, for that "+
      "would anger an entire orchard full of workers and armed overseers!\n");

  add_exit(RIDGE_DESERT+"d04.c","east",0,6,0);
  add_exit(RIDGE_DESERT+"d02.c","west",0,6,0);
  add_exit(RIDGE_DESERT+"d07.c","southwest",0,6,0);
  add_exit(RIDGE_DESERT+"d08.c","south",0,6,0);
  add_exit(RIDGE_DESERT+"d09.c","southeast",0,6,0);

}


