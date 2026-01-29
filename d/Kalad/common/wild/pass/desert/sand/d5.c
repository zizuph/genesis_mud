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
      "To the west, southeast and southwest are ways that appear to lead "+
      "between the surrounding sand dunes. "+
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
   add_item(({"ways","way"}),"Nothing more than a slight depression "+
      "between the rising sand dunes.\n");
   add_exit(CPASS(desert/sand/d4),"west",0,3);
   add_exit(CPASS(desert/sand/d9),"southeast","@@event",3);
   add_exit(CPASS(desert/sand/d8),"southwest",0,3);
}
event()
{
   set_alarm(3.0,0.0,"event_there");
   set_alarm(2.0,0.0,"event_here");
   return 0;
}
event_here()
{
   tell_room(TO,"With a great thundering noise, part of the sand dunes "+
      "to the southeast collapses, blocking that exit.\n");
   remove_exit("southeast");
   return 1;
}
event_there()
{
   tell_room(CPASS(desert/sand/d9),"With a great thunderous noise, part "+
      "of the sand dunes to the northwest collapses, blocking that exit.\n");
   call_other(CPASS(desert/sand/d9),"remove_exit","northwest");
   return 1;
}
