/* 
 * /d/Kalad/common/wild/pass/w44.c
 * Purpose    : Valley setting
 * Located    : South of Caravan Route
 * Created By : Antharanos Whenever
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Valley");
   set_long("A beautiful vista spreads out before you. However, what "+
      "wasn't obvious from further north were the darkened trees in this section "+
      "of the valley. Filling your entire field of view are the dark and "+
      "towering redwoods, for some unexplainable reason you have the strange "+
      "feeling of being watched. The "+
      "slopes of the Hespyre mountains are less sharp here and are low "+
      "enough in angle that the tree line is significantly higher here than "+
      "on other parts of the mountain range. The darkened vale continues to the "+
      "south.\n");
   add_item(({"towering redwoods","redwoods","towering redwood","redwood"}),
      "Massive trees that are as large as twenty feet across at the base "+
      "and rise dozens of feet into the sky. Their thick canopies of leaves "+
      "in conjunction with their proximity produce an abundance of darkness "+
      "beneath them, on the forest floor.\n");
   add_item(({"canopies","canopy","leaves"}),"They nearly block out the "+
      "sky.\n");
   add_item(({"forest floor","floor"}),"The ground is littered with "+
      "old leaves, brown in color because they are no longer alive.\n");
   add_item(({"slopes","hespyre mountains","mountains","mountain","mountain range","range"}),
      "They are perhaps only a third the height of the main mountain range "+
      "of the Hespyre mountains. However, this doesn't make them any less "+
      "impressive, as they are still dozens of times higher than the tallest "+
      "structure made by man.\n");
   add_exit("/d/Kalad/common/wild/pass/w43", "north",0,2);
  add_exit("/d/Kalad/common/wild/pass/wolf/w1", "south","@@block",2);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if (!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/wild/pass/npc/dwolf");
      ob1 -> move_living("xxx", TO);
   }
   if (!ob2)
      {
      ob2 = clone_object("/d/Kalad/common/wild/pass/npc/dwolf");
      ob2 -> move_living("xxx", TO);
      ob1 -> team_join(ob2);
   }
}
block()
{
   write("As you start heading south, the shadows seem to darken, the wind "+
      "stills and the chirping of birds dies down...Perhaps because of "+
      "some act of self-preservation or instinct, you turn back, away from "+
      "the gathering darkness.\n");
   return 1;
}
