#pragma strict_types
#include "../defs.h"

inherit (MORDOR_STD + "room");

public void
reset_udun_room() {
}

public nomask void
reset_mordor_room() {
  add_prop(ROOM_M_NO_SUN, 1);
  reset_udun_room();
}

public void
create_udun_room() {
}

public nomask void
create_mordor_room() {
  create_udun_room();
}
