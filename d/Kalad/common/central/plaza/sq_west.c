/* 
ROOM: West corner of Town Square
By:   Sebster
Date: Aug 27, 1994
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"
object ob1;

create_room()
{
   ::create_room();
   hear_bell = 3;
   
   set_short("The west corner of Town Square");
   set_long(
      "This is the west corner of Town Square. To the southwest you "+
      "see the Merchant Bank and, a bit more north, a run-down building "+
      "that must be the barracks of the guards here. Eastwards the center "+
      "of the square lies, with a huge statue in the middle. ");
   
   set_time_desc(
      "Several little children are playing bank-robber in the dirt.\n",
      "You see a very suspicious character playing with a lockpick and "+
      "scrutinizing the bank.\n"
   );
   
   add_exit(CENTRAL(plaza/sq_mon), "east", 0);
   add_exit(CENTRAL(plaza/sq_bank), "southwest", 0, -1, -1);
   add_exit(CENTRAL(barracks/entrance),"northwest","@@move_in",-1,-1);
   add_exit(CENTRAL(plaza/sq_north), "northeast", 0);
   add_exit(CENTRAL(plaza/sq_south), "southeast", 0);
   
   add_item("bank", 
      "A sturdy building, this bank guarantees your money's safety for "+
      "the modest fee.\n"
   );
   add_item(({"barrack","barracks"}),
      "A run-down stone building that probably is the guards sleeping and living "+
      "quarters. The presence of it makes the banks safety to be assured even more.\n");
   set_alarm(1.0,0.0,"reset_room");
}

reset_room()
{
   seteuid(getuid(TO));
   if (!objectp(ob1))
      {
      ob1 =  clone_object("/d/Kalad/common/central/npc/beggar");
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      ob1->command("emote arrives.");
   }
}



move_in()
{
   if(TP->query_base_stat(SS_DIS) < 50)
      {
      write("You start to walk through the door, but lack the will "+
         "to enter the barracks. You walk back again.\n");
      say(QCTNAME(TP) + " starts to walk towards the barracks, but lack "+
         "the courage to enter.\n");
      return 1;
   }
   TP->catch_msg(
      "You walk into the barracks and are met by the smell of "+
      "old sweat.\n");
   return 0;
}
