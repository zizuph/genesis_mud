inherit "/d/Gondor/common/room";
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"

create_room()
{
  set_short("In the Palantir-chamber of the White Towers");
  set_long("You are in a large circular chamber in the tall white tower\n"+
    "of Elostirion, the westmost of the 3 White Towers at the Tower Hills\n"+
    "east of Grey Havens. In the centre of the room is the Palantir!\n");
  add_prop(ROOM_I_INSIDE,1);
  add_exit("/d/Gondor/elessar/rooms/weathertop","east",0);
}

