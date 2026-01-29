// 2hp6.c 
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
	"   The passage slopes upward in three directions, "+
        "while a small tunnel leads downward into darkness.\n");

  DARK
  ALL;

  set_tell_time(60);
  add_tell("The sound of your heart beating echos loudly in "+
        "your ears.\n"); 
  add_tell("The air is noticeably moist.\n");
  add_tell("From somewhere nearby comes the muted sounds of "+
    	"rushing water.\n");
 

  AI(({"floor","dust"}), "Dark powdery dust covers the floor. "+
        "It looks like soot which has fallen from the ceiling.\n");
}
