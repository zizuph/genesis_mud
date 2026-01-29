/*
 * rum.c  - for the pub in Pelargir
 */

inherit "/std/drink";

#include "/sys/stdproperties.h"

create_drink() {
   set_name("rum");
   set_adj("strong");
   set_short("glass of strong rum");
   set_pshort("glasses of strong rum");
   set_long(break_string(
      "The rum has a strong pungent smell to it, and a light brown colour "+
      "that indicates a well-brewed rum.\n",70));
   set_drink_msg("*cough*  Strong stuff! A well-brewed batch of rum!\n");

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(55);     /* This is a small glass */
   set_alco_amount(46);
   add_prop(OBJ_I_WEIGHT,180);
   add_prop(OBJ_I_VOLUME,200);
}
