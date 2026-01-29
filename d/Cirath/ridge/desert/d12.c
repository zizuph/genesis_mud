 /* Agricultural fields, just west of Tyr.
  * Code (c) Dethraine, March 1998.
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
        "the nobles estates which feeds the populace of Tyr.\n");

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
      "leaves spread out in a fan-shaped formation. It is olacea, "+
      "a staple vegetable grown in Athas. Its leaves are often "+
      "served raw, as a salad, but can also be cooked.\n");

  add_cmd_item(({"food","crop","crops","olacea","leaves"}),
      ({"pick","take","harvest"}),"You dare not pick the crops, for that "+
      "would anger entire fields full of workers and armed overseers.\n");

  add_item(({"overseers","overseer"}),"Armed overseers are outnumbered "+
     "by slaves at most by a factor of 10:1. Like the slaves, "+
     "they are of varied race, but are invariably strong, and "+
     "are typically of a cruel and ruthless disposition. "+
     "They employ whips and cudgels to good effect, but one "+
     "notices that many an obsidian blade can also be found, "+
     "in their possession, for they must also protect against "+     
     "raiders, rampaging beasts, and wholescale insurrection.\n");

  add_exit(RIDGE_DESERT+"d13.c","east",0,6,0);
  add_exit(RIDGE_DESERT+"d09.c","northeast",0,9,0);
  add_exit(RIDGE_DESERT+"d08.c","north",0,6,0);
  add_exit(RIDGE_DESERT+"d07.c","northwest",0,9,0);
  add_exit(RIDGE_DESERT+"d11.c","west",0,6,0);
  add_exit(RIDGE_DESERT+"d15.c","southwest",0,12,0);
  add_exit(RIDGE_DESERT+"d16.c","south",0,8,0);
  add_exit(RIDGE_DESERT+"d17.c","southeast",0,9,0);

}


