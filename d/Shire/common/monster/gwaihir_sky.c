inherit "/std/room";

#include "/sys/stdproperties.h"

create_room() {
  set_short("Gwaihir's sky");
  set_long("Gwaihir uses this room to disappear from the game when "+
    "in flight.\n");
  add_prop(ROOM_I_INSIDE, 1);
}
