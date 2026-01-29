inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define SLAVE "/d/Kalad/common/wild/pass/drow/npc/h7_hum_slave"
object ob1;
object ob2;
object ob3;
object ob4;
object ob5;
object ob6;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("The slave pens");
   set_long("The slave pens of House Claddath.\n"+
      "Surprisingly, there is light within this room, not the magical light "+
      "produced by faerie fire, but the stinking and smelly light of several "+
      "torches mounted upon the dark black walls of this hollowed-out chamber. "+
      "Crudely-carved stone walls and floor characterize this chamber, the "+
      "holding area of the slaves owned by House Claddath. Unusual with "+
      "respect to its surroundings is the single, blood-red column of "+
      "light that rises from the center of this chamber and reaches up "+
      "to and through the ceiling far above.\n");
   add_item(({"slave pens","slave pen","pens","pen","holding area","area","hollowed-out chamber","chamber"}),
      "A filthy and disease-ridden cesspool.\n");
   add_item(({"torches","torch"}),
      "The battered bronze torches lie in their sconces upon the wall, barely "+
      "illuminating this pitiful and wretched place.\n");
   add_item(({"sconces","sconce"}),
      "Indentations within the walls where the torches have been placed.\n");
   add_item(({"dark black walls","dark walls","black walls","walls","wall","crudely-carved stone walls","stone walls","crudely-carved walls"}),
      "The strangely dark stone seems to absorb what little light the "+
      "torches ar giving off, as though such light was an affront to the "+
      "rock's very existence.\n");
   add_item(({"crudely-carved stone floor","stone floor","crudely-carved floor","floor"}),
      "A rough place where many a slave has tripped upon an uneven place "+
      "and never gotten up to stand again.\n");
   add_item(({"single column","single light","blood-red column","column","light"}),
      "A five-foot wide beam of scarlet light that rises from the floor "+
      "up to and through the ceiling above.\n");
   add_item(({"ceiling"}),
      "Nothing but dark rock is visible.\n");
   add_exit(CPASS(drow/house7/main_hall),"up",0,-1,1);
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(SLAVE);
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(SLAVE);
      ob2 -> move_living("M",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object(SLAVE);
      ob3 -> move_living("M",TO);
   }
   if(!ob4)
      {
      ob4 = clone_object(SLAVE);
      ob4 -> move_living("M",TO);
   }
   if(!ob5)
      {
      ob5 = clone_object(SLAVE);
      ob5 -> move_living("M",TO);
   }
   if(!ob6)
      {
      ob6 = clone_object(SLAVE);
      ob6 -> move_living("M",TO);
      tell_room(TO,"An uneven chorus of groans attracts your attention to a "+
         "huddled group of slaves.\n");
   }
}
