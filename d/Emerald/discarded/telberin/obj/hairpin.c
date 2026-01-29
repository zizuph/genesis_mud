inherit "/std/object";

#include "default.h"

void
create_object()
{
   set_name("hairpin");
   add_name("_puzzle_hairpin_");
   add_name("pin");
   set_short("used hairpin");
   set_long("This hairpin has been used a lot from the appearance of it. It " +
            "is made out of bronze.\n");
   set_adj("used");
   
   add_prop(OBJ_I_WEIGHT, 4);
   add_prop(OBJ_I_VOLUME, 3);
   add_prop(OBJ_M_NO_BUY, 1);
   add_prop(OBJ_I_VALUE, 6);
}

