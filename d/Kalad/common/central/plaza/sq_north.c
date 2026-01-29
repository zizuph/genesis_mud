/*
ROOM: North corner of Town Square
BY:   Sebster
DATE: Aug 27, 1994
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"
object ob1;
object ob2;
object ob3;

void
create_room()
{
   ::create_room();
   hear_bell = 3;
   
   set_short("The north corner of Town Square");
   set_long(
      "This is the north corner of Town Square. To the south you "+
      "see the massive city monument, and to the north the High Street "+
      "runs in between two important looking buildings. The westmost "+
      "construction is the illustrious City Council building, while "+
      "the east structure houses the Council of Lords.\n");
   
   set_time_desc(
      "Currently you see many politicians sneaking around the buildings "+
      "in the north.\n",
      "You see some shapes sneaking past you in the shadows of the night.\n");
   
   add_exit(CENTRAL(high-circle-north), "north");
   add_exit(CENTRAL(plaza/sq_st_ne), "east");
   add_exit(CENTRAL(plaza/sq_mon), "south");
   add_exit(CENTRAL(plaza/sq_st_nw), "west");
    add_exit(CENTRAL(plaza/cl_hall1), "northeast", 0, -1, -1);
    add_exit(CENTRAL(plaza/cc_hall1), "northwest", 0, -1, -1);
    add_exit(CENTRAL(plaza/sq_east), "southeast");
   add_exit(CENTRAL(plaza/sq_west), "southwest");
   
   
   add_item(({"building", "left building", "right building"}),
      "The City Coucil and Council of Lord buildings are almost "+
      "identical. They boast thick walls, small Gothic windows, and "+
      "white brick blackened by the smoke of many 'accidental' fires.\n"
   );
   set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
   if(!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/militia_officer");
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      ob1 -> command("say Come on you lazy bastards! Attention!! We have "+
         "work to do.\n");
   }
   if(!objectp(ob2)){
      ob2 = clone_object("/d/Kalad/common/central/npc/militia_plaza");
      ob2 -> arm_me();
      ob2 -> move_living("xxx",TO);
      ob1 ->team_join(ob2);
      ob2 -> command("say Guard duty again!\n");
      ob2 -> command("grumble");
   }
   if(!objectp(ob3)){
      ob3 = clone_object("/d/Kalad/common/central/npc/militia_plaza");
      ob3 -> arm_me();
      ob3 -> move_living("xxx",TO);
      ob1 -> team_join(ob3);
      ob3 -> command("sigh");
   }
}
