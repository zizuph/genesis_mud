/*
 *  wine.c  - wine in the pub in Pelargir
 */

inherit "/std/drink";

#include "/sys/stdproperties.h"

create_drink() {
   set_name("wine");
   add_name("bottle");
   set_pname("wines");
   add_pname(({"bottles"}));
   set_adj(({"glass","red"}));
   set_short("bottle of red wine");
   set_pshort("bottles of red wine");
   set_drink_msg("Ahh....that red wine was quite nice!\n");
   set_long(break_string(
      "The pungent red wine comes from the ripened grapes "
    + "that were harvested in the land of Lebennin some years ago.\n",70));

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(150);     /* This is a bottle */
   set_alco_amount(24);      /* 16% alcohol     */
   add_prop(OBJ_I_WEIGHT,810);
   add_prop(OBJ_I_VOLUME,830);
}
