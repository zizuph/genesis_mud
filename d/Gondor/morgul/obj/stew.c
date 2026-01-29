/* stew.c:  Food for the Red Eye Inn.  */

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("stew");
  add_name("bowl");
   set_adj("blackroot");
   set_short("bowl of blackroot stew");
    set_pname("bowls");
    add_pname("stews");
   set_pshort("bowls of blackroot stew");
   set_long(break_string(
    "The blackroot stew looks really delicious - for those who love "+
    "blackroots. Other will just see a pulpy mash giving off an acrid " +
    "stench. It might be edible, at least for orcs. \n", 75));
   add_prop(OBJ_I_VALUE, 0);
   set_amount(95);
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,92);
}

