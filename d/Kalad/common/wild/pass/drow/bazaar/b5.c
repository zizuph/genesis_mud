inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("At the center of the bazaar, Undraeth");
   set_long("This is the very center of the bazaar of Undraeth, and in "+
      "more ways than one, is also the very heart of the drow city of "+
      "Undraeth. Only here may merchants, traders and travellers come and "+
      "engage in commerce without fear of a quick death via a knife in the "+
      "back, or through some terrible spell. Though located hundreds of feet "+
      "below the surface and within one of the most evil cities known to "+
      "exist, there is a certain excitement about the place, an almost "+
      "carnival-like atmosphere. However, one gaze at the dark, towering "+
      "stalagmite homes of the drow quickly dispels that foolish notion.\n"+
      "A tent, its flap open, lies before you.\n");
   add_item(({"center","bazaar"}),
      "A place that bustles with trading and other commercial activities "+
      "one would normally attribute to surface cities.\n");
   add_item(({"drow city","city","undraeth"}),
      "The darkened stalagmite buildings of the gloomy city rise "+
      "threateningly over the bustling scene of the bazaar.\n");
   add_item(({"tent"}),
      "A black leather canvas that has been colorfully outlined in magical "+
      "faerie fire, making it glow red.\n");
   add_item(({"flap"}),
      "It has been folded aside, meaning that the tent is clear to enter.\n");
   add_exit(CPASS(drow/bazaar/b1),"west");
   add_exit(CPASS(drow/bazaar/b2),"north");
   add_exit(CPASS(drow/bazaar/b3),"east");
   add_exit(CPASS(drow/bazaar/b4),"south");
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
void
init()
{
   ::init();
   AA(enter,enter);
}
int
enter(string str)
{
   if(!str || str != "tent")
      {
      NF("Enter what? The tent perhaps?\n");
      return 0;
   }
   write("You duck your head and enter the tent.\n");
   set_alarm(1.0,0.0,"do_enter");
   return 1;
}
void
do_enter()
{
   TP->move_living("into the tent","/d/Kalad/common/wild/pass/drow/bazaar/mage_tent");
   return;
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/bazaar_merchant));
      ob1 -> move_living("M",TO);
      tell_room(TO,"One of the bazaar merchants appears before you.\n");
   }
}
