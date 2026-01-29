inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"

create_room()
{
  set_short("On the River Gwathlo, close to Lond Daer");
  set_long("You are close to the ancient city Lond Daer on the River Gwathlo.\n"+
      "The river runs southwest towards the ocean.\n");
  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
}
