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
      "tending the fields, with armed overseers ensuring that "+
      "they work as hard as they can. It is their labour on "+
      "the nobles estates which feeds the populace of Tyr. "+
      "The fields are bounded to the east by the immense "+
      "stone walls surrouding that city.\n");

  add_item(({"slaves"}),"Slavery does not discriminate based upon "+
      "race in the harsh environment of Athas. Humans, muls, "+
      "dwarves, and even the occasional halfling or elf can all "+
      "be seen toiling under the brutal heat of Athas's sun. "+
      "The life of a field working slave in "+
      "Athas is a brief and tortured one. Given only the "+
      "minimum amount of food and water necessary to survive, "+
      "they pour their efforts into the parched landscape, "+
      "in the hopes that it will yield enough food for "+
      "them as well as their overlords. Ruthless overseers "+
      "stand watch, ready to strike them for the slightest "+
      "lessening of their efforts. Those who dare to so much "+
      "as place their hands to their lips face a severe beating "+
      "or worse. Yet, it is their labour which allows the city-"+
      "state of Tyr to survive...\n");

  add_item(({"overseers"}),"Armed overseers are outnumbered "+
        "by slaves by at most a factor of 10:1. Like the slaves, "+
        "they are of varied race, but are invariably strong, and "+
        "are typically of a cruel and ruthless disposition. "+
        "They employ whips and cudgels to good effect, but one "+
        "notices that many an obsidian blade can also be found "+
        "in their possession, for they must also protect against "+     
        "raiders, rampaging beasts, and wholescale insurrection. "+
        "Even those who would be tempted to be of a kinder "+
        "heart realize that the only thing keeping them from "+
        "working the fields themselves is their ability to "+
        "discipline the mass of slaves.\n");

  add_item(({"crops","plants","crop","field","fields"}),
        "Vast fields of edible crops of diverse kinds surround "+
        "city of Tyr. A survey of them, however, reveals that "+
        "the better portion of them are stunted, yellowed, or "+
        "otherwise bear signs of the tenuous nature of Athasian "+
        "agriculture. Only the generous application of "+
        "water, slaves, and, it is rumoured, the magic of "+
        "Sorceror King, allows any substantial quantity of food "+
        "to be grown. Still, famine is a constant threat to "+
        "any who dwell in Athas.\n");

  add_item(({"walls","city walls"}),"Immense stone walls, tens of "+
        "feet in thickness serve to isolate Tyr from the harsh wilderness "+
        "of Athas. It would take a truly amazing force to break through "+
        "those walls.\n");

  add_cmd_item(({"walls", "city walls"}),({"climb","climb up"}), 
      "Not bloody likely!\n");

  add_cmd_item(({"food","crop","crops",}),
      ({"pick","take","harvest"}),"You dare not pick the crops, for that "+
      "would anger entire fields full of workers, and armed overseers.\n");

  add_exit(RIDGE_DESERT+"d09.c","north",0,6,0);
  add_exit(RIDGE_DESERT+"d08.c","northwest",0,9,0);
  add_exit(RIDGE_DESERT+"d12.c","west",0,6,0);
  add_exit(RIDGE_DESERT+"d16.c","southwest",0,12,0);
  add_exit(RIDGE_DESERT+"d17.c","south",0,8,0);
  add_exit(RIDGE_DESERT+"d18.c","southeast",0,9,0);
}


