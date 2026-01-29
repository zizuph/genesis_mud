/*
 * water_flask.c - a flask that contains water, for the Rangers, Jan 1995.
 */

#pragma save_binary

inherit "/std/drink";

#include "/sys/stdproperties.h"

create_drink() {
  set_name("flask");
  set_pname("flasks");
   set_adj("small");
  add_adj("water");
   set_short("small water-flask");
   set_pshort("small water-flasks");
   set_long(break_string(
    "This flask of water is rather small, and only contains about "+
    "half a pint. It is carved out of wood.\n",70));

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(55);      /* This is a pint */
   set_alco_amount(0);       /* 0% alcohol     */
   add_prop(OBJ_I_WEIGHT,150);
   add_prop(OBJ_I_VOLUME,190);
}