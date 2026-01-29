inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
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
      "The nearest sand dunes are to the south and east, while passages "+
      "lie to the west, north and southeast. "+
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
   add_item(({"passages","passage"}),"Ways through and among the huge "+
      "ridges of the sand dunes.\n");
   add_exit(CPASS(desert/sand/d25),"west",0,3);
   add_exit(CPASS(desert/sand/d21),"north",0,3);
   add_exit(CPASS(desert/sand/d30),"southeast",0,3);
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
