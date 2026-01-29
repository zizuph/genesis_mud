#pragma save_binary

inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "guild.h"

void
create_room()
{
  set_short("Corridor");
  set_long("This is a corridor in the quarters of Angmar Army. "+
         "It continues to the south and north. To the east you see a pub.\n");

  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

  add_exit(THIS_DIR+"c1", "north");
  add_exit(THIS_DIR+"c3", "south");
  add_exit(THIS_DIR+"pub", "east");
}
