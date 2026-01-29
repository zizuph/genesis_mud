inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("In the mountains");
   set_long("An abundance of slate-grey rocks surrounds you on all sides, "+
      "making the world seem composed solely of mountainous terrain. "+
      "The rocky path abruptly stops here, at the edge of a steep cliff. "+
      "The path continues to the northeast, heading higher up into the "+
      "Desertrise mountains. "+
      "A warm, carressing wind gently blows about the area. "+
      "The cruel rays of the Kaladian sun strike you from above, searing "+
      "your exposed flesh.\n");
   add_item(({"slate-grey rocks","rocks","rock"}),"Large, featureless "+
      "stones that have fallen from the mountains.\n");
   add_item(({"rocky path","path"}),"A rugged trail that winds its "+
      "way through this rocky terrain.\n");
   add_item(({"base","mountains","mountain"}),"The dark, grey peaks "+
      "rise high above you, daunting in their size.\n");
   add_item(({"kaladian sun","sun"}),"Its fierce rays nearly blind you!\n");
   add_item(({"edge","steep cliff","cliff"}),"A rocky precipice "+
      "overlooking the rugged terrain around you.\n");
   add_exit(CPASS(desert/mount/m7),"down",0,5);
   add_exit(CPASS(desert/mount/m9),"northeast",0,4);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/m_ogre));
      ob1 -> my_stuff();
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(CPASS(npc/m_ogre));
      ob2 -> my_stuff();
      ob2 -> move_living("M",TO);
      tell_room(TO,"Two mountain ogres arrive from down the path.\n");
      ob1 -> team_join(ob2);
   }
}
