inherit "/std/food";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_food()
{
    set_name("hay");
    set_adj("pile of");
    set_long("A large and fresh pile of hay. To weary pack animals it "+
      "looks very tempting.\n");
    set_amount(200);
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,5000);
}
