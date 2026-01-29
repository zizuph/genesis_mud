inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

create_room()
{
  set_short("In the Palantir-room in the Tower of Amon Sul");
  set_long("You are in a circular shaped room in the top of the Tower of\n"+
    "Amon Sul, on Weathertop. Windows allow sunlight into the room, but\n"+
    "the main attraction is not the view - but the Palantir!\n");
  add_prop(ROOM_I_INSIDE,1);
  add_exit("/d/Gondor/elessar/rooms/annuminas","north",0);
  add_exit("/d/Gondor/elessar/rooms/elostirion","west",0);
  add_exit("/d/Gondor/elessar/rooms/osgiliath","south",0);
}

