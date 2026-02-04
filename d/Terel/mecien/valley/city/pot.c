inherit "/std/container";

#include "/sys/stdproperties.h";
#include <money.h>

create_container() {
   set_name("pot");
   set_short("clay pot");
   set_adj("clay");
   set_long("A well made clay pot, useful for carrying things.\n");
   add_prop(CONT_I_WEIGHT,     1000);   /* It weighs 1 Kg            */
   add_prop(CONT_I_MAX_WEIGHT, 10000);   /* It can contain up to 5 Kg  */
   add_prop(CONT_I_VOLUME,     3000);   /* It measures 3 Ltr         */
   add_prop(CONT_I_MAX_VOLUME, 8000);   /* It can contain 10 Ltr       */
   add_prop(CONT_I_RIGID, 1);
   add_prop(CONT_I_TRANSP, 1); /* You can see the insides. */
   add_prop(OBJ_I_VALUE,10);    /* Value 40 cc*/
   
}
