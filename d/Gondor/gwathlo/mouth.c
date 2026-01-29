inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"

create_room()
{
  set_short("At the mouth of River Gwathlo");
  set_long("The Gwathlo runs into the ocean here.\n");
  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
}
