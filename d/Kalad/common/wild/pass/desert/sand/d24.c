inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Within the endless sand dunes");
   set_long("All around you, in great sloping mounds are "+
      "the huge glittering ridges of the sand dunes. "+
      "The loose sand that fills your parched throat makes travel through "+
      "this harsh clime extremely difficult, for "+
      "it seems as if you sink lower and lower with each step, and even "+
      "the smallest of sand dunes is a hindrance to travel. "+
      "Passages lead off to the west, north and southeast. "+
      "The scorching rays of the Kaladian sun hammer down on the dunes "+
      "all about you, so intense is the heat that ripples of air are "+
      "clearly visible.\n");
   add_item(({"great sloping mounds","great mounds","sloping mounds","mounds","mound","huge glittering ridges","huge ridges","glittering ridges","ridges","sand dunes","sand dune","dunes","dune"}),
      "Formed from the continual action of the harsh desert winds, the great "+
      "collections of sands are ever-shifting in the landscape, threatening "+
      "anything of permanence with ignoble burial.\n");
   add_item(({"loose sand","sand"}),"The tiny, fine granules slip through "+
      "your grasp.\n");
   add_item(({"kaladian sun","sun"}),"The harshly brilliant orb hangs "+
      "in the sky, scorching the land beneath it with its rays of light.\n");
   add_item(({"passages"}),"Ways through the sand dunes.\n");
   add_exit(CPASS(desert/sand/d23),"west",0,3);
   add_exit(CPASS(desert/sand/d20),"north",0,3);
   add_exit(CPASS(desert/sand/d29),"southeast",0,3);
}
