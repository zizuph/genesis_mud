inherit "/d/Gondor/common/room";
#include <stdproperties.h>

create_room() {
  set_short("Hall");
  set_long(
"This is a great wooden hall, perfect for feasts and discussions. Right\n"+
"now, though, it's empty.\nThe street is to the west.\n\n");
  add_exit("/d/Gondor/rohan/edoras/path7","west",0);
  add_prop(ROOM_I_INSIDE,1);
}
