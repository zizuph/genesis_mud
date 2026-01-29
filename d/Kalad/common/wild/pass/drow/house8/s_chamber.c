inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define SLAVE "/d/Kalad/common/wild/pass/drow/npc/h8_dg_slave"
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
   add_prop(ROOM_I_LIGHT,0);
   set_short("Chamber of the slaves");
   set_long("This disgusting hellhole must be the residence of the "+
      "unfortunate slaves of House Noquar. The only source of ventilation for "+
      "this cavernous room is the entrance that lies in the southwest, "+
      "otherwise it is little more than a dressed up cavern. Offal lies in "+
      "great stinking piles all over the room, while puddles of urine and "+
      "worse lie in the lower portions of the floor.\n");
   add_item(({"chamber","room","hellhole","slave pit","pit"}),
      "It is where you are now, unfortunately.\n");
   add_item(({"entrance"}),
      "It is the entrance as well as the exit out of this slave pit.\n");
   add_item(({"offal","great stinking piles","great piles","stinking piles","piles","pile"}),
      "The putrid mounds rise as high as a deep gnome's waist, roughly the height "+
      "of an average drow's knees. A horrific odor emanates from them.\n");
   add_item(({"puddles","puddle","urine"}),
      "The dark yellow liquid impossibly enough, makes the room smell even "+
      "worse than it is, no easy feat given the sheer volume of offal here.\n");
   add_item(({"floor"}),
      "The rough, unworked stone floor is riddled with low spots, which are "+
      "presently filled with puddles of urine. and worse.\n");
   add_exit(CPASS(drow/house8/entrance),"southwest","@@msg",-1,1);
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
      tell_room(TO,"Several deep gnomes emerge from the piles of offal.\n");
   }
}
