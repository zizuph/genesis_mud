inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Entrance to a dark cave");
   set_long("This is the entrance to a dark, foul-smelling cave. Darkness "+
      "reigns supreme to the west, deeper inside this cave. To the east is the "+
      "way out. The interior here is of a dark grey stone and appears to be "+
      "natural in origin.\n");
   add_item(({"entrance","dark cave","foul-smelling cave","cave"}),
      "It is where you are, perhaps you should look around.\n");
   add_item(({"interior"}),
      "The inside of this cave is rough in texture and many small rocks "+
      "litter the floor, indicating a natural origin.\n");
   add_item(({"small rocks","rocks","rock"}),
      "Fist-sized stones that litter the ground.\n");
   add_item(({"ground"}),
      "It is rough in texture and littered with many small rocks.\n");
   add_item(({"dark grey stone","dark stone","grey stone","stone"}),
      "A rock type similar to the stone that comprises this mountain range.\n");
   add_exit(CPASS(desert/mount/o2),"west");
   add_exit(CPASS(desert/mount/m10),"east");
}
