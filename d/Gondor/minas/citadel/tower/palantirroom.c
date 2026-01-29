inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

create_room()
{
  set_short("In the Palantir-chamber in the White Tower of Minas Tirith");
  set_long("You are in a domed chamber up in the high levels of the White\n"+
    "Tower in Minas Tirith. The view offered by the windows is spectacular,\n"+
    "but what catches your attention is the Palantir!\n");
  add_prop(ROOM_I_INSIDE,1);
  add_exit("/d/Gondor/elessar/rooms/osgiliath","down",0);
}

