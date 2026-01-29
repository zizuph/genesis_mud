inherit "/d/Earthsea/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

void
create_earthsea_room()
{
    set_short("On the sea");
    set_long("The dark blue sea surrounds the ship. You see "+
      "the coast of Calia quite close now. On a large rock "+
      "you spot a golden-haired mermaid who seems to be "+
      "waving to you.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
