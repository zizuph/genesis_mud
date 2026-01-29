inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Tunnel");
   set_long("You're within a dismal tunnel corridor that heads north "+
      "and southwest into inky darkness. Numerous small stones are littered "+
      "across the ground while the walls and ceiling possess rough, pitted "+
      "surfaces, indicative of a natural origin. A putrid odor reaches "+
      "your nostrils, causing some discomfort.\n");
   add_item(({"dismal tunnel corridor","dismal corridor","tunnel corridor","corridor","tunnel"}),
      "The dark passageway in which you find yourself inside of.\n");
   add_item(({"inky darkness","darkness"}),
      "A lightlessness darker than your worst, tortured nightmares.\n");
   add_item(({"small stones","stones","stone"}),
      "Fist-sized chunks of rock that lay about the ground.\n");
   add_item(({"walls","wall","ceiling"}),
      "By their rough, pitted textures, it is apparent that they were formed "+
      "through natural proccesses.\n");
   add_exit(CPASS(desert/mount/o2),"north");
   add_exit(CPASS(desert/mount/o6),"southwest");
}
