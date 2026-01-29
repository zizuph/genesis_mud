inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* by korat */

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Within the dwarven city of Underhome");
   set_long("The path seems to widen up a bit here, heading "+
      "north and south along a building to the east. A shimmer "+
      "of red light is visible just north of you, lighting up "+
      "a doorway heading into the building. To the south you "+
      "see the outline of a small plaza with a statue in "+
      "the center.\n");
   add_item(({"buildings","building","wall"}),
      "The building looks to be in a good shape, and are probably "+
      "being in use by some of the deep dwarves that live in Underhome.\n");
   add_item(({"path","street","streets"}),"You can "+
      "walk along a large trodden path that the dwarven boots has "+
      "managed to clear.\n");
   add_exit(CPASS(dwarf/s17),"north");
   add_exit(CPASS(dwarf/s19),"south");
   set_noshow_obvious(1);
}
