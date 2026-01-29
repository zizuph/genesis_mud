/*
 *   Orc meats, carried by orcs in Moria.
 */

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("meat");
   add_name("hunk");
  add_name("flesh");
   set_adj("bloody");
  set_short("bloody hunk of flesh");
  set_pshort("bloody hunks of flesh");
   set_long("This bloody hunk of flesh looks like the standard rations"+
    " of orcs living in Moria.\n");
   add_prop(OBJ_I_VALUE, 10);
  set_amount(250);
   add_prop(OBJ_I_WEIGHT,560);
   add_prop(OBJ_I_VOLUME,205);
}
