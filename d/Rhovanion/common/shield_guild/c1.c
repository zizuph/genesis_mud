#pragma save_binary

inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "guild.h"

void
create_room()
{
  set_short("Corridor");
  set_long("This is a corridor in the quarters of Angmar Army  which "+
     "continues to the south. To the north is a big hall and you can "+
     "hear a lot of noise coming from there. To the east you see a shop.\n");

  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

  add_exit(THIS_DIR+"train", "north");
  add_exit(THIS_DIR+"c2", "south");
  add_exit(THIS_DIR+"shop", "east");
  add_exit(THIS_DIR+"post", "west");
}
