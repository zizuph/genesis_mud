// 2hp2.c 
// uses boriska's random exit generator
// grace

#include "../local.h"
#include "2hp.h"

inherit STD2HP;

void
create_spur_room()
{
     ::create_spur_room();

  SHORT("a dark passage");
   LONG("The rough stone walls are dark and dull, swallowing "+
        "the light.  The ceiling is low and blackened with soot.\n"+
        "   The silence is as oppressive as the "+
	"eternal sameness of the passage is disorienting. "+
  	" The floor slopes downward in two directions and "+
        "upward the other.\n");

   DARK
  ALL;
  set_tell_time(60);
  add_tell("The sound of your heart beating echos loudly in "+
        "your ears.\n"); 
  add_tell("The air is stale and tastes of the dust your "+
       	"feet have disturbed.\n");
  add_tell("You feel the urge to sneeze.\n");
  add_tell("Little puffs of disturbed dust rise from the floor.\n");

  AI(({"floor","dust"}), "Dark powdery dust covers the floor. "+
        "It looks like soot which has fallen from the ceiling.\n");

}
