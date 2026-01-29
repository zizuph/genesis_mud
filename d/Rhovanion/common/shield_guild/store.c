/*
 * Milan
 */

#pragma save_binary

inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "guild.h"

void
create_room()
{
  set_short("Store room");
  set_long("This is the store room of Angmar's Army.\n");

  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

  add_exit(THIS_DIR+"priv", "west");
}
