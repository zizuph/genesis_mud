inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"


void
create_object()
{
   set_name(({"fish", "rotten fish", "_flotsam_r_fish_"}));
   set_adj("rotten");
   set_short("rotten fish");
   set_long("A large, green-scaled rotten fish that smells " +
      "really bad, and probably tastes worse. You wouldn't " +
      "feed this to your worst enemy. \n");
   add_prop(OBJ_I_VOLUME, 300);
   add_prop(OBJ_I_WEIGHT, 500);
}
