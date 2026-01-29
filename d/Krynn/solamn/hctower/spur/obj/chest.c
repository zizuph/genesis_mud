// chest
// grace aug 1994

inherit "/std/receptacle";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "../local.h"

void
create_container()
{
   set_name("chest");
   add_name(({"box", "iron chest"}));
   set_adj(({"small", "iron"}));
   
   set_short("small iron chest");
   set_long( "This small iron chest has leather trimmings and "
         + "a simple iron lock.\n");

   AI("lock", "It is simply a keyhole.\n");
   AI("keyhole", "It looks like a small key would fit inside.");

   add_prop(CONT_I_MAX_WEIGHT,  200000); /* 200 kilos */
   add_prop(CONT_I_MAX_VOLUME,  200000); /* 200 liters */
   add_prop(CONT_I_RIGID, 1);
   add_prop(OBJ_M_NO_GET, "The iron chest is much too heavy to be lifted.\n");
   set_key(LOCK_1);
   add_prop(CONT_I_LOCK,0);
   add_prop(CONT_I_CLOSED,1);
   } 



