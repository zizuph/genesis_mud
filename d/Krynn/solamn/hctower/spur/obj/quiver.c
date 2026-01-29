// archer's quiver, container for arrows.
// grace aug 1994

inherit "/std/container";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "../local.h"

void
create_container()
{
   set_name("quiver");
   set_adj("archer's");
   set_short("quiver");
   LONG("This is a leather case made for holding arrows.\n");
   add_prop(CONT_I_MAX_WEIGHT,  5000); /* 5 kilos */
   add_prop(CONT_I_MAX_VOLUME,  5000); /* 5 liters */
   add_prop(CONT_I_RIGID, 1);
}     
