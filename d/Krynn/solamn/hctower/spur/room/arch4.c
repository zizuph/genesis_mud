// arch 4.c
// grace aug 1994

inherit "/d/Krynn/solamn/hctower/spur/room/std_arch.c";
#include "../local.h"
#define HALL \
({  \
      ROOM + "hall2", \
      ROOM + "hall3", \
      ROOM + "hall4", \
      ROOM + "hall5", \
      ROOM + "hall6", \
 })

object guard1, guard2, guard3, guard4, guard5;

reset_spur_room()
{
  if (!guard1)
    (guard1 = clone_object(ARCHER))->move_living(0,this_object());
  if (!guard2)
    (guard2 = clone_object(ARCHER))->move_living(0,this_object());
    guard2->set_leader(guard1);
    guard1->team_join(guard2);
  if (!guard3)
    (guard3 = clone_object(ARCHER))->move_living(0,this_object());
    guard3->set_leader(guard1);
    guard1->team_join(guard3);
  if (!guard4)
    (guard4 = clone_object(ARCHER))->move_living(0,this_object());
    guard4->set_leader(guard1);
    guard1->team_join(guard4);
  if (!guard5)
    (guard5 = clone_object(ARCHER))->move_living(0,this_object());
    guard5->set_leader(guard1);
    guard5->team_join(guard1);
}      

void
create_spur_room()
{
   
   AE(ROOM + "stair3", "up", 0);
   SHORT("Central archer's station");
   AI(({"west wall", "west slit", "west slits"}),
      "Beyond the slits in the western wall you see the aquaduct. "+
      "On the opposite wall you can see similar arrow slits.\n");
   AI(({"east wall", "east slit", "east slits", "passageway"}),
      "@@hall_desc@@");
   AI("water","You can't see anything, but you can hear it.\n");
   ACI("water",({"listen to","hear"}), "The sound of running "
      +"water is ever-present in this long, narrow room. You can't "
      +"decide whether the sound is abrasive or soothing to your "
      +"ears.\n");      
   make_the_room("  A series of narrow openings line the east and " +
      "west walls. The room is thrice as long as it is wide, and " +
      "a stairway leads up from the northwest corner to the " +
      "second floor.  You can hear the sound of running water.\n");
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


