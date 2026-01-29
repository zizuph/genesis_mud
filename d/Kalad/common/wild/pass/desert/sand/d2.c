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
      "A way through the sand dunes lies to the northeast, southeast and southwest. "+
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
   add_item(({"way"}),"Nothing more than a slight depression among the "+
      "sand dunes.\n");
   add_exit(CPASS(desert/sand/d1),"northeast",0,3);
   add_exit(CPASS(desert/sand/d4),"southeast",0,3);
   add_exit(CPASS(desert/sand/d3),"southwest","@@event",3);
}
event()
{
   set_alarm(3.0,0.0,"event_there");
   set_alarm(2.0,0.0,"event_here");
   return 0;
}
event_here()
{
   tell_room(TO,"With a great thunderous noise, part of the sand dunes "+
      "to the southwest collapses, blocking that exit.\n");
   remove_exit("southwest");
   return 1;
}
event_there()
{
   tell_room(CPASS(desert/sand/d3),"With a great thunderous noise, part "+
      "of the sand dunes to the northeast collapses, blocking that exit.\n");
   call_other(CPASS(desert/sand/d3),"remove_exit","northeast");
   return 1;
}
