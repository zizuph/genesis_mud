#pragma save_binary

inherit "/d/Gondor/common/room";
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_room()
{
  set_short("A dark winding passage");
  set_long(BS("The passage is so narrow here that you are brushing the stony "+
    "wall on either side. You hear the noise of rushing water to the north. "+
    "The passage enters utter darkness to the west, and continues east.\n"));
  add_item("wall","The stony walls are rough and narrow.\n");
  add_exit(RANGER_ITH_DIR+"passage4","west",0);
  add_exit(RANGER_ITH_DIR+"passage6","east",0);
  add_prop(ROOM_I_INSIDE,0);
  add_prop(ROOM_I_LIGHT,1);
}