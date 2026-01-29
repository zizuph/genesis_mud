// lockbox
// grace aug 1994

inherit "/std/receptacle";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "../local.h"

void
create_container()
{
   set_name("lockbox");
   add_name("box");
   add_name("lock box");
   set_adj(({"dusty", "old"}));
   
   set_short("lockbox");
   set_long(
         "This is a sturdy wooden box with iron trimmings and "
         + "a simple iron lock.\n");

   AI("lock", "It is made of iron.\n");

   add_prop(CONT_I_MAX_WEIGHT,  200000); /* 200 kilos */
   add_prop(CONT_I_MAX_VOLUME,  200000); /* 200 liters */
   add_prop(CONT_I_RIGID, 1);
   add_prop(OBJ_M_NO_GET, "The box is much too heavy to be lifted.\n");
   set_key(LOCK_1);
   add_prop(CONT_I_LOCK,1);
   add_prop(CONT_I_CLOSED,1);
   }
