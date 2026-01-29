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
  set_short("Old armory");
  set_long("This dusty room was once the Armory for those soldiers " +
        "who had proven themselves. They'd be able to get better " +
        "weapons and armours. Now, the ceiling has collapsed, " +
        "burying everything inside.\n");
   
  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */


  add_exit(NEW_ANGMAR + "priv", "north");
}
