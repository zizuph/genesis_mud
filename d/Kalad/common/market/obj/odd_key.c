inherit "/std/key";

#include "/d/Kalad/defs.h"

create_key()
{

    set_adj("odd");
    add_adj("bent");
    add_adj("little");
    set_long(BS(
      "At first glance this odd little key appears " +
      "quite ordinary. However, it is bent at a strange " +
      "angle. You hope it still works.\n"));
}
