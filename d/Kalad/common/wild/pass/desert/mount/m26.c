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
   set_long("An apparently endless sea of slate-grey rocks surrounds "+
      "you from every direction, making the world seem composed solely of this "+
      "rocky wasteland. A rocky path travels to the north and to the south. "+
      "A dry wind races among the mountains, causing an eerie cadence of "+
      "sound that echoes amonst them. "+
      "Above, the unending rays from the Kaladian sun fall down upon you with "+
      "its merciless might.\n");
   add_item(({"slate-grey rocks","rocks","rock"}),"Large, featureless "+
      "stones that have fallen from the mountains.\n");
   add_item(({"rocky path","path"}),"A rugged trail that winds its "+
      "way through this rocky terrain.\n");
   add_item(({"base","mountains","mountain"}),"The dark, grey peaks "+
      "rise high above you, daunting in their size.\n");
   add_item(({"kaladian sun","sun"}),"Its fierce rays nearly blind you!\n");
   add_item(({"edge","steep cliff","cliff"}),"A rocky precipice "+
      "overlooking the rugged terrain around you.\n");
   add_exit(CPASS(desert/mount/m25),"north","@@giant_block",4);
   add_exit(CPASS(desert/mount/m27),"south",0,4);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/stone_giant));
      ob1 -> arm_me();
      ob1 -> move_living("xxx",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(CPASS(npc/stone_giant));
      ob2 -> arm_me();
      ob2 -> move_living("xxx",TO);
      ob1 -> team_join(ob2);
   }
}
giant_block()
{
   object *ob;
   int pres,i;
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   for(i = 0; i < sizeof(ob); i++)
   {
      if(ob[i]->query_name() == "Giant")
         {
         pres = 1;
       }
   }
   if(pres == 1)
      {
      write("The stone giant is in the way!\n");
      say(QCTNAME(TP) + " tries to leave north but runs into the stone giant!\n");
   }
   return pres;
}
