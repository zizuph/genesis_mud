inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
#define SW "/d/Kalad/common/wild/pass/uc/npc/hum_skel"
object ob1;
object ob2;
object ob3;
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("At the bottom of the chasm");
   set_long("At the bottom of the chasm.\n"+
      "Bones, hundreds, if not thousands of bones lie scattered all over "+
      "the bottom of this chasm. Some of them are piled high in great mounds "+
      "that rise far overhead, while most of them are strewn haphazardly about, "+
      "as though a fearsome wind had rushed through here. The surrounding "+
      "rock is as it was higher up, composed of some unusually dark material. "+
      "Escape from this place seems quite improbable, for the walls of "+
      "the chasm are perfectly vertical.\n"+
      "The bottom of the chasm continues to the west and east, while a passage "+
      "leads to the south.\n");
   add_item(({"bottom","chasm"}),
      "A large gash within the ground, it is, unfortunately, where you are.\n");
   add_item(({"bones","bone"}),
      "The remnants of numerous creatures, some human...others not quite so.\n");
   add_item(({"great mounds","mounds","mound","great mound"}),
      "Rising nearly twenty feet in height, they easily tower over you, but "+
      "fall far short of the distance to the top of the chasm.\n");
   add_item(({"surrounding rock","rock"}),
      "It is composed of some unusually dark material that appears to absorb "+
      "the minutest of light that shines upon it.\n");
   add_item(({"walls","wall"}),
      "They lie at a ninety degree angle to the floor, and are as smooth "+
      "as ice, offering no handholds whatsoever.\n");
   add_item(({"floor","ground"}),
      "It is composed of strangely dark rock.\n");
   add_item(({"ceiling"}),
      "It is impossible to view, as you are too far down in the chasm.\n");
   add_item(({"passage"}),
      "An area of darkness amidst the greater darkness of the surrounding "+
      "chasm, it would appear to lead to another chamber or room.\n");
   add_exit(CPASS(uc/d2),"west","@@msg",2,1);
   add_exit(CPASS(uc/d6),"south","@@msg2",2,1);
   add_exit(CPASS(uc/d4),"east","@@msg",2,1);
   set_alarm(1.0,0.0,"reset_room");
}
void
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(SW);
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(SW);
      ob2 -> arm_me();
      ob2 -> move_living("M",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object(SW);
      ob3 -> arm_me();
      ob3 -> move_living("M",TO);
      ob1 -> team_join(ob2);
      ob1 -> team_join(ob3);
      tell_room(TO,"Several piles of bones suddenly begin moving.\n");
      tell_room(TO,"They form into skeletal figures!\n");
   }
}
void
init()
{
   ::init();
   AA(climb,climb);
}
int
climb(string str)
{
   if(!str || str != "up")
      {
      NF("Climb where? Up?\n");
      return 0;
   }
   write("You try to climb up the sheer walls of the chasm, but fail.\n");
   say(QCTNAME(TP) + " tries to climb up the sheer walls of the chasm, but fails.\n");
   return 1;
}
msg()
{
   write("The crunch of bones echoes weirdly as you move.\n");
   return 0;
}
msg2()
{
   write("The crunch of bones echoes weirdly as you continue down the passage.\n");
   return 0;
}
