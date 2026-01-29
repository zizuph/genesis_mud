// 2hp1.c 
// uses boriska's random exit generator
// grace
// make exit for pushing armoire away.

#include "../local.h"
#include "2hp.h"
inherit STD2HP;
#define CLOSET ("/d/Krynn/solamn/hctower/spur/room/closet")

int door_opened = 0;
int close_alarm_id = 0;
void reset_spur_room();

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

   AI(({"arch","archway"}), "It is blocked by a piece of wood.\n");     

   AI(({"floor","dust"}), "Dark powdery dust covers the floor.\n");
   AI(({"wood", "piece"}), "The wood has the smoothness and "+
    	"sheen of a piece of furniture.\n");       
   reset_spur_room();
}

mixed
find_hp(object searcher, string what)
{
   NF("The door is already opened.\n");
   if (door_opened)
	return 0;

   if (searcher->query_skill(110) > 24)
     {
         say(QCTNAME(searcher) + " discovers the way to move aside "+
            "the piece of wood blocking the archway.\n");
         set_alarm(2.0, 0.0, "pass_found");  
         return "Your sensitive fingers find a small depression in one "+
                "of the stone blocks of the arch.\n";
     }        
   return 0;
}

void
pass_found()
{
    tell_room(TO, "With a puff of pine-scented air, the piece of wood blocking "+
             "the arch swings aside, revealing a dark hole.\n");

    door_opened = 1;
    close_alarm_id = set_alarm(20.0, 0.0, "pass_close");
    add_exit(CLOSET, "south", 0);
    call_other(CLOSET, "pass_open");
}

void
pass_up()
{
    tell_room(TO, "With a puff of pine-scented air, the piece of wood blocking "+
             "the arch swings aside, revealing a dark hole.\n");
    door_opened = 1;
    add_exit(CLOSET, "south", 0);
    close_alarm_id = set_alarm(20.0, 0.0, "pass_close");
}

void
pass_close()
{
   if (close_alarm_id)
     {
       remove_alarm (close_alarm_id);
       close_alarm_id = 0;
     }
   
   tell_room(CLOSET, "The wall swings quickly back into place.\n");

   remove_exit("south");   
   door_opened = 0;

}

void 
reset_spur_room()
{
   door_opened = 0;
   close_alarm_id = 0;
   remove_exit("south");
}
