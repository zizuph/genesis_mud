inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("At an intersection of tunnels in a dark cave");
   set_long("You are at an intersection of two darkness-filled tunnels. "+
      "One heads east from here towards a distant point of light, while the other "+
      "runs north to south, being utterly lightless. Small stones litter "+
      "the ground, though they provide no obstacle to travel. A faint, "+
      "undeterminable odor pervades this place.\n");
   add_item(({"intersection"}),
      "Its where you are standing.\n");
   add_item(({"darkness-filled tunnels","tunnels","tunnel"}),
      "They lead to the north, east and south.\n");
   add_item(({"point of light","light"}),
      "A tiny circle of light far to the east, it may be a way out of "+
      "this cave system.\n");
   add_item(({"small stones","stones","stone"}),
      "Roughly the size of a human fist, they abound on the ground.\n");
   add_item(({"ground"}),
      "Rough and uneven in texture, it is littered with many small stones.\n");
   add_exit(CPASS(desert/mount/o3),"north");
   add_exit(CPASS(desert/mount/o1),"east");
   add_exit(CPASS(desert/mount/o7),"south");
}
