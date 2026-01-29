inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Within the endless sand dunes");
   set_long("Rising skyward in great sloping mounds all around you are "+
      "the huge glittering ridges of the sand dunes. "+
      "An abundance of loose sand beneath makes your travel extremely difficult, for "+
      "it seems as if you sink lower and lower with each step, and even "+
      "the smallest of sand dunes is a great obstacle to travel. "+
      "Numerous ways lead through the great mounds of the sand dunes here. "+
      "The continual, burning light of the Kaladian sun strikes the dunes "+
      "all around, the intensity of the reflection is nearly blinding.\n");
   add_item(({"great sloping mounds","great mounds","sloping mounds","mounds","mound","huge glittering ridges","huge ridges","glittering ridges","ridges","sand dunes","sand dune","dunes","dune"}),
      "Formed from the continual action of the harsh desert winds, the great "+
      "collections of sands are ever-shifting in the landscape, threatening "+
      "anything of permanence with ignoble burial.\n");
   add_item(({"loose sand","sand"}),"The tiny, fine granules slip through "+
      "your grasp.\n");
   add_item(({"kaladian sun","sun"}),"The harshly brilliant orb hangs "+
      "in the sky, scorching the land beneath it with its rays of light.\n");
   add_item(({"ways","way"}),"Furrows within the mounds of the sand "+
      "dunes, it seems passable, unlike the dunes themselves.\n");
   add_exit(CPASS(desert/sand/d16),"west",0,3);
   add_exit(CPASS(desert/sand/d11),"northwest",0,3);
   add_exit(CPASS(desert/sand/d12),"north",0,3);
   add_exit(CPASS(desert/sand/d22),"southeast","@@event",3);
   add_exit(CPASS(desert/sand/d21),"southwest",0,3);
}
event()
{
   set_alarm(3.0,0.0,"event_there");
   set_alarm(2.0,0.0,"event_here");
   return 0;
}
event_here()
{
   tell_room(TO,"Without warning, an avalance of sand occurs to the southeast, "+
      "where part of the sand dunes are collapsing. Moments later, after the "+
      "dust has cleared, you discover the exit to the southeast no longer exists.\n");
   remove_exit("southeast");
   return 1;
}
event_there()
{
   tell_room(CPASS(desert/sand/d22),"Without warning, an avalance of "+
      "sand occurs to the northwest, where part of the sand dunes are "+
      "collapsing. Moments later, after the dust has cleared, you discover the "+
      "exit to the northwest no longer exists.\n");
   call_other(CPASS(desert/sand/d22),"remove_exit","northwest");
   return 1;
}
