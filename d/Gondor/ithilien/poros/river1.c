inherit "/d/Gondor/common/room";
#include <stdproperties.h>

void
create_room()
{
  set_short("on the river Poros, close to the Fords of Poros");
  set_long("The river Poros runs southwest towards the Anduin.\n");
  add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
