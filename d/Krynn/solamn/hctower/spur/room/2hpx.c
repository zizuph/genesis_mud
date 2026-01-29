// 2hp1.c 
// uses boriska's random exit generator
// grace
// make exit for pushing armoire away.

#include "../local.h"
#include "2hp.h"

inherit STD2HP;

int hid_pass_open = 0;    /* Hidden passage not open */
object next_room = ROOM + "closet.c";

void
create_spur_room()
{
     ::create_spur_room();

  SHORT("a dark passage");
  LONG("The rough stone walls are dark and dull, swallowing "+
        "the light.  The ceiling is low and blackened with soot.\n"+
        "   There is an archway here, but passage "+
	"through it is blocked by a piece of wood. The floor "+
  	"slopes sharply downward into darkness.\n");

   DARK;
   ALL;

  add_search("wood", 3, "find_hp", 1);
  add_search("arch", 3, "find_hp", 1);
  add_search("archway", 3, "find_hp", 1);

  set_tell_time (60);
  add_tell("The muted sound of voices comes from beyond the "+
 	"blocked archway.\n");
  add_tell("The air is stale and tastes of the dust your "+
       	"feet have disturbed.\n");
  add_tell("You feel the urge to sneeze.\n");

   AI(({"floor","dust"}), "Dark powdery dust covers the floor.\n");
   AI(({"wood", "piece"}), "The wood has the smoothness and "+
    	"sheen of a piece of furniture.\n");       

}

mixed
find_hp(object searcher, string what)
{
        if (hid_pass_open)
            return 0;
        if (searcher->query_skill(110) > 25)
           {
             AE(ROOM + "kn2", "south", 0);    
              say(QCTNAME(searcher) + " discovers the way to move aside "+
                "the piece of wood blocking the archway.\n");
              hid_pass_open = 1;
              next_room->pass_found();
              return "Your sensitive fingers find a small depression in one "+
                "of the stone blocks of the arch.\nThe piece of wood blocking "+
                "the archway swings aside, revealing a dark hole.\n";
            }
        return 0;
}

void
pass_found()
{
   tell_room(TO, "With a puff of pine-scented air, the piece of wood blocking " +
             "the arch swings aside, revealing a dark hole.\n");
   hid_pass_open = 1;
   add_exit(ROOM + "closet", "south", 0);
}

int
query_hid_pass()
{
   return hid_pass_open;
}

