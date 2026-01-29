// arch2.c
// grace aug 1994

inherit "/d/Krynn/solamn/hctower/spur/room/std_arch.c";
#include "../local.h"

object guard1, guard2, guard3, guard4, guard5, guard6;

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
      (guard5 = clone_object(KNIGHT))->move_living(0,this_object());
   guard5->set_leader(guard1);
   guard5->team_join(guard1); 
   if (!guard6)
      (guard6 = clone_object(KNIGHT))->move_living(0,this_object());
   guard6->set_leader(guard1);
   guard6->team_join(guard1); 
}      

void
create_spur_room()
{
   
   AE(ROOM + "stair1", "north", 0);
   AE(ROOM + "arch1", "northwest", 0);
   AE(ROOM + "arch3", "southwest", 0);
   SHORT("Relief archer's station");
   AI("west wall", "Dark stone with a doorway in the northwest "+
      "and another in the southwest.");
   AI("east wall", "This wall has been carved from the living " +
      "rock of Westgate Pass.\n");
   AI(({"table", "tables", "bench", "benches"}), "Made of heavy "+
      "vallenwood imported from Solace.\n");
   ACI(({"table", "tables", "bench", "benches"}), ({"sit","sit on"}),
      "You settle comfortably onto it.\n");
   make_the_room("  The room is large and horse-shoe shaped, with " +
      "benches and tables for relief archers to wait comfortably.\n");
   reset_spur_room();
}


