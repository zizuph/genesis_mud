inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"

create_room()
{
  set_short("Somewhere in the open sea");
  set_long("You are somewhere in the open sea.\n");
  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
}
