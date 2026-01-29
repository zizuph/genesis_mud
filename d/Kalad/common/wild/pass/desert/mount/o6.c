inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;
object ob3;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Small chamber");
   set_long("You are within a slightly oval chamber, its walls, floor "+
      "and ceiling rough to the touch and pitted and scarred with a number "+
      "of imperfections. A gagging, foul stench permeates every corner of this "+
      "chamber but seems strongest near the center, where a large pile of "+
      "rotting flesh lies. The floor beneath is partially covered with "+
      "numerous small stones. To the northeast lies nothing but darkness.\n");
   add_item(({"slightly oval chamber","oval chamber","chamber"}),
      "A room roughly twenty feet across at its widest point, and just "+
      "past sixteen feet at its narrowest.\n");
   add_item(({"walls","wall"}),
      "The sides of the chamber are scarred and pitted, probably due to "+
      "whoever carved it out of the inside of this mountain.\n");
   add_item(({"floor"}),
      "The uneven stone floor is partially covered under a number of small "+
      "stones.\n");
   add_item(({"ceiling"}),
      "It is just over ten feet from the floor, for the most part. Parts "+
      "of the ceiling are lower, though there are no true stalactites here.\n");
   add_item(({"large pile of rotting flesh","large pile","pile","pile of rotting flesh","rotting flesh","flesh"}),
      "Over a dozen human bodies, all stripped naked lie in a great pile "+
      "at the center of this chamber. Their bloated, putrid bodies shows "+
      "that they have been dead for several days. Each of the bodies bears "+
      "many bite marks, and several have had various body parts ripped or "+
      "chewed off.\n");
   add_item(({"small stones","stones","stone"}),
      "Fist sized rocks that lie scattered around on the floor. Several "+
      "of them are colored a faded red.\n");
   add_exit(CPASS(desert/mount/o7),"northeast");
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/mo_scout));
      ob1 -> my_stuff();
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(CPASS(npc/mo_scout));
      ob2 -> my_stuff();
      ob2 -> move_living("M",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object(CPASS(npc/mo_scout));
      ob3 -> my_stuff();
      ob3 -> move_living("M",TO);
      tell_room(TO,"Several ogres emerge from the darkness.\n");
   }
}
