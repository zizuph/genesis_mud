/*
 * Angmar guild rooms
 * opened as nothing but a shell for old times
 * Finwe, October 2002
 */
inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <stdproperties.h>

void
create_room()
{
  set_short("Corridor");
  set_long("This is a quiet corridor in the quarters of Angmar Army which " +
        "continues to the south. To the north is a big hall, silent " +
        "for many years. To the east you see a shop.\n");

  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

  add_exit(NEW_ANGMAR + "train", "north");
  add_exit(NEW_ANGMAR + "c2", "south");
  add_exit(NEW_ANGMAR + "shop", "east");
  add_exit(NEW_ANGMAR + "post", "west");
}
