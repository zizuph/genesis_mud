/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon(){
   set_name(({"sword", "longsword", "mystic sword"}));
   set_adj("holy");
   set_short("longsword");
   set_long("A beautiful longsword. A silver traced blade\n" +
      "inscribed with symbols. The pommel studded with\n" +
      "seven bright emeralds, the hilt decorated with\n" +
      "intricate silver design and ivory inlaid.\n");
   set_hit(35);
   set_pen(34);
   set_wt(W_SWORD);
   set_dt(W_IMPALE | W_SLASH);
   add_prop(OBJ_I_LIGHT, 3);
   add_prop(OBJ_I_WEIGHT, 10000);
   add_prop(OBJ_I_VOLUME, 5000);
/*   add_prop(OBJ_I_VALUE, comp_value(45)); */
}
