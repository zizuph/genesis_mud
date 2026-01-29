inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"

create_room()
{
  set_short("Somewhere on the River Gwathlo");
  set_long("The Gwathlo River runs southwest towards the ocean.\n");
  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
}
