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
  set_long("This is a deserted corridor in the quarters of Angmar Army. "+
         "It continues to the south and north. To the east you see a pub.\n");

  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

  add_exit(NEW_ANGMAR + "c1", "north");
  add_exit(NEW_ANGMAR + "c3", "south");
  add_exit(NEW_ANGMAR + "pub", "east");
}
