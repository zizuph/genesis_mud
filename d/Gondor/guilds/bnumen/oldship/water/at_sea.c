inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"

void
create_room()
{
  set_short("Somewhere along the coast of Gondor");
  set_long("You are somewhere along the coast of Gondor.\n");
  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
}
