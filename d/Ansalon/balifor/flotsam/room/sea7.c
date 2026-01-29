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
   set_short("Out at sea");
   set_long("Out at sea.\n");
   add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
   
   reset_flotsam_room();
}
