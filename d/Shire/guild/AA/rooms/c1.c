#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "../guild.h"

inherit SHIRE_ROOM;

void
create_room()
{
  set_short("Corridor");
  set_long("This is a corridor in the quarters of Angmar Army  which "+
     "continues to the south. To the north is a big hall and you can "+
     "hear a lot of noise coming from there. To the east you see a shop.\n");

  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

  add_exit(AA_DIR+"rooms/train", "north");
  add_exit(AA_DIR+"rooms/c2", "south");
  add_exit(AA_DIR+"rooms/shop", "east");
  add_exit(AA_DIR+"rooms/post", "west");
}
