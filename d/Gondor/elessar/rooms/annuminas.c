inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

create_room()
{
  set_short("In the Palantir-room of the Tower of Annuminas");
  set_long("You are in a circular chamber under the dome of the Tower of\n"+
    "the Sunset by Lake Nenuial in Arnor. The chilly winds of Arnor\n"+
    "sweep across Annuminas, through the open windows of the tower. In the\n"+
    "centre of the room is the Palantir!\n");
  add_prop(ROOM_I_INSIDE,1);
  add_exit("/d/Gondor/elessar/rooms/weathertop","south",0);
}

