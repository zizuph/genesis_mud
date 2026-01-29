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
      "You are presently between a massive sand dune to the west and "+
      "north, and a much smaller dune to the south. Three ways lead "+
      "through the dunes here, one to the southwest, another to the "+
      "east and a third to the southeast. "+
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
   add_item(({"massive sand dune"}),"A towering mass of sand that casts "+
      "its shadow across the dunes.\n");
   add_item(({"much smaller dune"}),"A relatively small sand dune, "+
      "as compared to the one in the west and north.\n");
   add_exit(CPASS(desert/sand/d19),"southwest",0,3);
   add_exit(CPASS(desert/sand/d14),"east",0,3);
   add_exit(CPASS(desert/sand/d20),"southeast",0,3);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/sandling));
      ob1 -> move_living("M",TO);
      tell_room(TO,"The sand before you shifts slightly.\n");
   }
}
