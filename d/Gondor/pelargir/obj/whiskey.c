/*
 * whiskey.c  - for the pub in Pelargir
 */

inherit "/std/drink";

#include "/sys/stdproperties.h"

create_drink() {
   set_name("whiskey");
   set_pname("whiskeys");
   set_adj("dry");
   set_short("glass of dry whiskey");
   set_pshort("glasses of dry whiskey");
   set_long(break_string(
      "The dry whiskey is of a golden-brownish colour and has a strong smell to it. It was "
    + "produced somewhere in Belfalas sometime during the last decade.\n",70));
   set_drink_msg("*cough*  Strong stuff! Not bad at all!\n");

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(50);     /* This is a small glass */
   set_alco_amount(40);      /* 35% alcohol           */
   add_prop(OBJ_I_WEIGHT,240);
   add_prop(OBJ_I_VOLUME,240);
}
