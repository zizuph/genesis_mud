// 2hp5.c 
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
        "   You are now completely disoriented. "+
	" Looking at the stone walls you find it difficult "+
  	"to determine which direction you entered from.\n"+
	"   The passage arcs upward in two directions and "+
        "downward in another.\n");

  DARK
  ALL;

  set_tell_time(60);
  add_tell("The sound of your heart beating echos loudly in "+
        "your ears.\n"); 
  add_tell("The air is stale and tastes of the dust your "+
       	"feet have disturbed.\n");
  add_tell("You feel the urge to sneeze.\n");
  add_tell("Little puffs of disturbed dust rise from the floor.\n");

  AI(({"floor","dust"}), "Dark powdery dust covers the floor.\n"+
        "It looks like soot which has fallen from the ceiling.\n");


}
