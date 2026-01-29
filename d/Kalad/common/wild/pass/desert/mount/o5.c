inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Large chamber");
   set_long("This is a slightly larger chamber than the one to the "+
      "north, and is also shaped in the form of a circle, rather than a "+
      "square. In the center lies a great heap of bones while scattered "+
      "around the chamber's floor are various chunks of flesh. A putrid "+
      "odor assails your nostrils, nearly driving you mad with its terrible "+
      "stench. In the south lies a large boulder. To the north is a crude "+
      "archway leading to the other chamber.\n");
   add_item(({"large chamber","chamber"}),
      "It is the excavation within this mountain range that you're currently "+
      "inside of.\n");
   add_item(({"center"}),
      "A great heap of bones lies there.\n");
   add_item(({"great heap of bones","heap of bones","bones","bone"}),
      "The skeletal remains of dozens of human beings. Many of the bones "+
      "bear marks indicative of chewing and slashing.\n");
   add_item(({"floor"}),
      "The rough stone ground is littered with numerous chunks of decaying "+
      "flesh.\n");
   add_item(({"chunks","chunk","flesh"}),
      "The torn, bloodied and partially eaten remains of many human beings.\n");
   add_item(({"large boulder","boulder"}),
      "A rock nearly eight feet across and five feet in height. Other than "+
      "its large size there is nothing special about it.\n");
   add_item(({"crude archway","archway"}),
      "Nothing more than a gaping hole in the wall, leading north.\n");
   add_item(({"walls","wall","ceiling"}),
      "Part of the heart of this mountain range, the dark grey stone bears a "+
      "strength greater than any man-made wall or barrier.\n");
   add_exit(CPASS(desert/mount/o4),"north");
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/mo_chief));
      ob1 -> my_stuff();
      ob1 -> move_living("M",TO);
      tell_room(TO,"The darkness seems to lessen a bit, and from it emerges "+
         "an ogre.\n");
   }
}
