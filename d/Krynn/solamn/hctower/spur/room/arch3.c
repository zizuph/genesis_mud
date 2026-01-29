// arch3.c
// grace aug 1994

inherit "/d/Krynn/solamn/hctower/spur/room/std_arch.c";
#include "../local.h"
#define HALL \
({  \
      ROOM + "hall6", \
      ROOM + "hall5", \
      ROOM + "hall4", \
 })

object guard1, guard2;

reset_spur_room()
{
   if (!guard1)
      (guard1 = clone_object(ARCHER))->move_living(0,this_object());
   if (!guard2)
      (guard2 = clone_object(ARCHER))->move_living(0,this_object());
   guard2->set_leader(guard1);
   guard1->team_join(guard2);
}      

void
create_spur_room()
{
   
   AE(ROOM + "arch2", "east", 0);
   SHORT("Southeast archer's station");
   AI(({"west wall", "west slit", "west slits", "passageway"}),
      "@@hall_desc@@");
   AI(({"east wall", "east slit", "east slits"}),
      "Smooth stone wall with a doorway.\n");
   make_the_room("  This room is a squarish cell with a " +
      "series of narrow openings lining the west wall.\n");
   reset_spur_room();
}

string hall_desc()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;
   
   roomfiles = HALL;
   inv = ({});
   for (i = 0; i < sizeof(roomfiles); i++)
   {
      if ((room = find_object(roomfiles[i])) != 0)
         inv += all_inventory(room);
   }
   
   if (inv && sizeof(inv) > 0)
      {
      live = FILTER_LIVE(inv);
      if (sizeof(live) > 0)
         return ("Through the narrow slits you can see shadowy figures " +
         "that look like " + COMPOSITE_LIVE(live) + ".\n");
   }
   return ("The passage beyond the arrow slits seems to be clear.\n");
}
