#include "/d/Ansalon/balifor/flotsam/local.h"
#include "/d/Ansalon/common/defs.h"

inherit FLOTSAM_OUT;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("The Bloodsea of Istar");
   set_long("The red waters of the Bloodsea of Istar. \n");
   add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
   
   reset_flotsam_room();
}
