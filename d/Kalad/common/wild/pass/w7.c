/* 
 * /d/Kalad/common/wild/pass/w7.c
 * Purpose    : Road
 * Located    : On the Caravan Route
 * Created By : Antharanos Shrug
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
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
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("The Caravan Route");
   set_long("You are travelling along the Caravan Route.\n"+
      "The way west heads slightly upwards into a closed-in box canyon. "+
      "All about you are the immense mountains of the Hespyre range. Almost lost "+
      "among the towering heights of the mountains are the no less "+
      "impressive redwoods, which blanket the lower slopes of the range. "+
      "A large cleft within the sheer walls of the mountains lies just to "+
      "the north, apparently leading to another valley. The Caravan Route "+
      "continues eastward, deeper into the Hespyre mountains.\n");
   add_item(({"caravan route","route","way"}),"A cobblestoned roadway that "+
      "appears worn due to heavy usage and the harsh effects of time and "+
      "weather.\n");
   add_item(({"immense mountains","hespyre range","hespyre mountains","mountain","range","immense mountains","hespyre mountain"}),
      "Craning your neck to take in the full sight of the mountains, their "+
      "sheer size and cold beauty make you feel as insignificant as a bug "+
      "compared with a human being. The mountains of the range cast a dark "+
      "shadow over the land.\n");
   add_item(({"impressive redwoods","impressive redwood","redwoods","redwood","lower slopes","lower slope","slopes","slope"}),
      "Giant redwood trees, as large as twenty feet across at the base "+
      "cover the lower slopes of the mountains. On the higher slopes, think "+
      "blankets of snow are visible.\n");
   add_item(({"large cleft","cleft"}),"A gash in the rock face of the mountain "+
      "range, it seems to lead down into another valley, though you cannot "+
      "tell for certain, due to the twisting walls within the valley.\n");
   add_item(({"sheer walls","sheer wall","walls","wall"}),"The "+
      "unclimbable sides of the mountains.\n");
   add_exit("/d/Kalad/common/wild/pass/w6", "west",0,3);
   add_exit("/d/Kalad/common/wild/pass/w22", "north",0,2);
   add_exit("/d/Kalad/common/wild/pass/w8", "east",0,2);
   set_alarm(2.0,0.0,"reset_room");
}

reset_room()
{
   if(!ob2)
      {
      ob2 = clone_object("/d/Kalad/common/wild/pass/citadel/npc/brigand");
      ob2 -> arm_me();
      ob2 -> move_living("M",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object("/d/Kalad/common/wild/pass/citadel/npc/brigand");
      ob3 -> arm_me();
      ob3 -> move_living("M",TO);
   }
   if(!ob4)
      {
      ob4 = clone_object("/d/Kalad/common/wild/pass/citadel/npc/brigand");
      ob4 -> arm_me();
      ob4 -> move_living("M",TO);
   }
   if(!ob5)
      {
      ob5 = clone_object("/d/Kalad/common/wild/pass/citadel/npc/ogre");
      ob5 -> arm_me();
      ob5 -> move_living("M",TO);
   }
   if(!ob6)
      {
      ob6 = clone_object("/d/Kalad/common/wild/pass/citadel/npc/ogre");
      ob6 -> arm_me();
      ob6 -> add_prop(OBJ_I_HIDE, 20);
      ob6 -> move_living("M",TO);
   }
   if(!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/wild/pass/citadel/npc/bandit_overlord");
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      tell_room(TO,"A huge half-ogre steps out on the road in front of you.\n");
   }
   ob1 -> team_join(ob2);
   ob1 -> team_join(ob3);
   ob1 -> team_join(ob4);
   ob1 -> team_join(ob5);
   ob1 -> team_join(ob6);
}
