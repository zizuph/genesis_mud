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
  set_long("On a path amongst fields of crops controlled by "+ 
        "Tyr's nobles. Isolated groups of slaves toil in these "+
        "fields, supervised by stern overseers.\n");
        
  add_item(({"crops","plants","crop","field","fields"}),
        "The fields are filled with a low growing crop, which you "+
        "identify as neep. The root of the neep plant is a common "+
        "item in Athasian cuisine, while the yellowish stubble "+
        "which passes for leaves is commonly used as fodder. It "+
        "is not presently in season.\n");

  add_item(({"slaves","slave"}),"Slavery does not discriminate "+
      "based upon race in the harsh environment of Athas. Humans, "+
      "muls, dwarves, and even the occasional halfling or elf "+
      "can all be seen toiling under the brutal heat of Athas's sun. "+
      "Armed overseers ensure that the slaves work to "+
      "their fullest capacity. The slaves in these fields of "+
      "unripe neep are engaged in the thankless task of weeding.\n");
        
  add_item(({"overseers","overseer"}),"Armed overseers are outnumbered "+
     "by slaves at most by a factor of 10:1. Like the slaves, "+
     "they are of varied race, but are invariably strong, and "+
     "are typically of a cruel and ruthless disposition. "+
     "They employ whips and cudgels to good effect, but one "+
     "notices that many an obsidian blade can also be found, "+
     "in their possession, for they must also protect against "+     
     "raiders, rampaging beasts, and wholescale insurrection.\n");

  add_cmd_item(({"food","crop","crops","neep"}),
      ({"pick","take","harvest"}),"The roots are not yet ripe, and "+
      "you have no use for fodder.\n");

  add_exit(RIDGE_DESERT+"d18.c","east",0,6,0);
  add_exit(RIDGE_DESERT+"d13.c","north",0,6,0);
  add_exit(RIDGE_DESERT+"d12.c","northwest",0,9,0);
  add_exit(RIDGE_DESERT+"d16.c","west",0,8,0);
/*
  add_exit(RIDGE_DESERT+"d20.c","southwest",0,12,0);
  add_exit(RIDGE_DESERT+"d21.c","south",0,8,0);
  add_exit(RIDGE_DESERT+"d22.c","southeast",0,12,0);
*/

}


