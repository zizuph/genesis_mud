inherit "/std/object";

#include <stdproperties.h>

#include "defs.h"

void create_object()
{
 set_name("_karg_catapult_design_plans_");
 add_name("plans");
 set_short("catapult design plans");
 set_long("This is design plans of new type of catapult, which "+
   "kargs are planning to use to conquire Gont. It was designed "+
   "by finest of Karg Empire engineers. It's designed to be "+
   "installed on warships and can shoot fireballs for very long "+
   "range, hitting target with very good accuracy.\n");

 add_prop(OBJ_I_WEIGHT,200);
 add_prop(OBJ_I_VOLUME,200);
}

