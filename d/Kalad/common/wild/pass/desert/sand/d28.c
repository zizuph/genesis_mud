inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
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
      "Passages through the dunes lie in several directions, and the "+
      "closest sand dunes lie just to the northwest and east. To the "+
      "south is nothing but barren flatlands. "+
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
   add_item(({"passages","passage"}),"Ways through the dunes surrounding "+
      "you.\n");
   add_item(({"barren flatlands","flatlands","flatland"}),"Nothing "+
      "but a flat desolate waste, littered here and there with small rocks "+
      "and the occasional cactus.\n");
   add_exit(CPASS(desert/sand/d23),"northeast",0,3);
   add_exit(CPASS(desert/flat/f2),"south","@@block",3);
}
block()
{
   write("You try to venture south but are immediately overcome with "+
      "sunstroke. You barely manage to crawl back to the dunes.\n");
   return 1;
}
