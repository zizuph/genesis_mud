inherit "/std/torch";
#include "/sys/stdproperties.h"

void
create_torch()
{

   set_value(55 + random(35));
   set_strength(1);
   set_time(1500);
   set_short("large torch");
   set_name("torch");
   add_name("large torch");
   set_long("This torch is nothing more than a piece of rotted cloth hung over "+
   "a stick. The cloth looks tough though.\n");


   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 150);

}
