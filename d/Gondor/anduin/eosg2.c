/*
 * anduin/eosg2.c
 */
#include "/d/Gondor/defs.h"
inherit (COMMON_DIR + "room");
#include <stdproperties.h>

void
create_room()
{
  set_short("On the River Anduin close to Eastern Osgiliath");
  set_long("You are somewhere on the river Anduin that is running south " +
    "towards its mouth in the Bay of Belfalas. The eastern shore " +
    "is not far from here. Ruins like dark shadows are strewn all " +
    "over the river bank, prominent among them the sad remains of " +
    "a mighty stone bridge.\n");
  add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
