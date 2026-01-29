inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Within the dwarven city of Underhome");
   set_long("You seem to be at the southern side of a small "+
      "plaza situated inbetween several buildings that has "+
      "survived the destiny of destruction and pillaging. "+
      "From here you can walk both to the northeast and northwest, "+
      "making a turn around "+
      "a monument in the center of this old plaza. Another road leads "+
      "to the southwest.\n");
   add_item(({"buildings","bilding"}),
      "The buildings looks to be in a good shape, and you can see "+
      "in the read, weak light pouring out of the door of the northeastern "+
      "one, some dwarves walking.\n");
   add_item("plaza","The plaza seems to be surrounded by some buildings, "+
      "that dwarves walks in and out of. In the center you see a large "+
      "monument.\n");
   add_item(({"path","street","streets"}),"Among some rubble you can "+
      "walk along a large trodden path that the dwarven boots has "+
      "managed to clear.\n");
   add_item(({"monument","statue"}),
      "The monument is of a broad dwarf sitting on a horse.\n");
   add_exit(CPASS(dwarf/s22),"northwest");
   add_exit(CPASS(dwarf/s20),"northeast");
   add_exit(CPASS(dwarf/s23),"southwest");
   set_noshow_obvious(1);
}
