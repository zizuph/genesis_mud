inherit "/d/Genesis/ship/cabin";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include "/d/Gondor/common/lib/time.h"

void
create_cabin()
{
  set_short("A dark and narrow space under a tarpaulin in a boat");
  set_long(BS("This is a dark and narrow place under a tarpaulin. \n"));
  add_exit(OSG_DIR + "ferry/in_ferry", "aft", 0);
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_LIGHT,0);
}
