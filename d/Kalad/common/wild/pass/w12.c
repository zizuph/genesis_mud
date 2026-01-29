/* 
 * /d/Kalad/common/wild/pass/w12.c
 * Purpose    : Road
 * Located    : Caravan Route out of Kabal
 * Created By : Antharanos  
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("The Caravan Route");
   set_long("You are travelling along the Caravan Route.\n"+
      "The way west eventually leads towards the famed city of Kabal. "+
      "All about you are the immense mountains of the Hespyre range. Almost lost "+
      "among the towering heights of the mountains are the no less "+
      "impressive redwoods, which blanket the lower slopes of the range. "+
      "The Caravan Route, which winds its way past the sheer walls of the mountains, "+
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
      "cover the lower slopes of the mountains. On the higher slopes, thin "+
      "blankets of snow are visible.\n");
   add_item(({"sheer walls","sheer wall","walls","wall"}),"The "+
      "unclimbable sides of the mountains.\n");
   add_exit("/d/Kalad/common/wild/pass/w11", "west",0,2);
   add_exit("/d/Kalad/common/wild/pass/w13", "east",0,2);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if (!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/wild/pass/npc/hmlion");
      ob1 -> move_living("xxx", TO);
   }
}
