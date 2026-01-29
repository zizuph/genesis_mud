#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
   set_short("Passage");
   set_long("This is part of what was once a guardroom. "+
         "The guardroom proper exists to the west, through a rotted door, "+
         "and to the south there is a passageway.\n");

   add_item("door","The door has rotted over centuries of exposure "+
      "to the dry atmosphere.\n");

   add_exit(CASTLE_DIR + "shop","west",);
   add_exit(CASTLE_DIR + "3k4","north",);
   add_exit(CASTLE_DIR + "3k8","southeast",);
}
