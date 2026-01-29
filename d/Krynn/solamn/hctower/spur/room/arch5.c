// arch5.c
// grace aug 1994

inherit "/d/Krynn/solamn/hctower/spur/room/std_arch.c";
#include "../local.h"

object guard1, guard2, guard3, guard4;

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
}      

void
create_spur_room()
{
   SHORT("Western archer's station");
   AI(({"east wall", "east slit", "east slits"}),
      "Beyond the slits in the eastern wall you see the aquaduct. "+
      "On the opposite wall you can see similar arrow slits.\n");
   AI(({"west wall", "western wall"}), "You see two doorways, one in " +
      "the northwest corner, the other in the southwest.\n");
   AI("water","You can't see anything, but you can hear it.\n");
   ACI("water",({"listen to","hear"}), "The sound of running "
      +"water is ever-present in this long, narrow room. You can't "
      +"decide whether the sound is abrasive or soothing to your "
      +"ears.\n");      
   set_noshow_obvious(1);
   AI(({"doorway","doorways","northwest doorway","southwest doorway"}),
       "Doorless openings lead to the northwest and southwest.\n");
  AE(ROOM + "pass4l1", "southwest", 0);
   AE(ROOM + "pass2l1", "northwest", 0);      
   make_the_room("  A series of narrow openings line the east wall." +
       "  The room is twice as long as it is wide, and two doorways " +
       "open into it from the northwest and southwest corners." +
       "  You can hear the sound of running water.\n");      
    reset_spur_room();
}


