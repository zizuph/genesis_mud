inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Inside a temple");
   set_long("You seem to be at a dead end inside a temple that has "+
      "avoided the destiny of destruction and pillaging. "+
      "Back southwest you will leave this place that makes your blood "+
      "freeze, but your lightsource doesn't maange to penetrate "+
      "into the pure darkness there.\n");
   add_item(({"temple","temples","temple ruin","temple ruins"}),
      "This temple has avoided the destruction, either through pure "+
      "luck or by some other means of protection.\n");
   add_item(({"path","street","streets"}),"Among all the rubble you can "+
      "walk along a small trodden path that the dwarven boots has "+
      "managed to clear.\n");
   add_item(({"exits","exit"}),"You see one that "+
      "continues further southwest into "+
      "pure darkness.\n");
   add_exit(CPASS(dwarf/temple/t5),"southwest");

   set_noshow_obvious(1);
}