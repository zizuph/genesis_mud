inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Bend in the tunnel");
   set_long("You've reached a bend in the tunnel. Two ways lead from "+
      "this point, west where a strange odor seems to be emanating from, "+
      "and south where it is slightly less intense. The rough texture of "+
      "the tunnel walls would seem to indicate a natural origin. Giving "+
      "credence to that assumption is the lack of supports for the tunnel "+
      "ceiling. Littering the ground are numerous small stones.\n");
   add_item(({"bend"}),
      "Where the tunnel takes a sharp turn.\n");
   add_item(({"tunnel"}),
      "A dark passage within this cave system.\n");
   add_item(({"tunnel walls","wall"}),
      "Rough and riddled with rocky projections, it appears to be natural "+
      "in origin.\n");
   add_item(({"tunnel ceiling","ceiling"}),
      "It lies above you and is similar to the rest of the tunnel in that "+
      "it is rough in texture.\n");
   add_item(({"ground"}),
      "The rough stone floor is covered here and there with many small stones.\n");
   add_item(({"small stones","stones","stone"}),
      "Small, fist-sized rocks of a dark grey color.\n");
   add_exit(CPASS(desert/mount/o4),"west");
   add_exit(CPASS(desert/mount/o2),"south");
}
