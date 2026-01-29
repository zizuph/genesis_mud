inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_object()
{
   set_short("pile of rubble");
   add_name("rubble");
   add_name("pile");
   set_long("A large pile of demolished stone, it is utterly worthless.\n");
   add_prop(OBJ_I_WEIGHT,900000); /* 900 kilograms ~ 2000 lbs */
   add_prop(OBJ_I_VOLUME,900000);
}
