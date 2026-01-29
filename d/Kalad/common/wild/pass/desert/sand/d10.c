inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Within the endless sand dunes");
   set_long("Towering in great sloping mounds around you are the "+
      "huge glittering ridges of the sand dunes. "+
      "The loose sand beneath you makes travel extremely difficult, for "+
      "it seems as if you sink lower and lower with each step, and even "+
      "the smallest of sand dunes is a great barrier to travel. "+
      "Four ways lead through the sand dunes here, to the northwest, "+
      "northeast, southwest and southeast. "+
      "The harsh, unrelenting light of the Kaladian sun strikes the dunes "+
      "all around, the intensity of the reflection is nearly blinding.\n");
   add_item(({"great sloping mounds","great mounds","sloping mounds","mounds","mound","huge glittering ridges","huge ridges","glittering ridges","ridges","sand dunes","sand dune","dunes","dune"}),
      "Formed from the continual action of the harsh desert winds, the great "+
      "collections of sands are ever-shifting in the landscape, threatening "+
      "anything of permanence with ignoble burial.\n");
   add_item(({"loose sand","sand"}),"The tiny, fine granules slip through "+
      "your grasp.\n");
   add_item(({"kaladian sun","sun"}),"The harshly brilliant orb hangs "+
      "in the sky, scorching the land beneath it with its rays of light.\n");
   add_item(({"ways","way"}),"Furrows in the sand dunes that are narrowly "+
      "passable.\n");
   add_exit(CPASS(desert/sand/d6),"northwest",0,3);
   add_exit(CPASS(desert/sand/d7),"northeast",0,3);
   add_exit(CPASS(desert/sand/d15),"southeast",0,3);
   add_exit(CPASS(desert/sand/d14),"southwest","@@event",3);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/sand_mar));
      ob1 -> move_living("M",TO);
      tell_room(TO,"The sand before you shifts slightly.\n");
   }
}
event()
{
   set_alarm(3.0,0.0,"event_there");
   set_alarm(2.0,0.0,"event_here");
   return 0;
}
event_here()
{
   tell_room(TO,"Suddenly, part of the sand dunes to the southwest collapses, "+
      "a huge dust cloud blocks your view for several moments and when you can "+
      "see again, the exit to the southwest is no longer there.\n");
   remove_exit("southwest");
   return 1;
}
event_there()
{
   tell_room(CPASS(desert/sand/d14),"Suddenly, part of the sand dunes to the "+
      "northeast collapses, a huge dust cloud blocks your view for several "+
      "moments and when you can see again, the exit to the northeast is no "+
      "longer there.\n");
   call_other(CPASS(desert/sand/d14),"remove_exit","northeast");
   return 1;
}
