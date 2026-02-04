inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon(){
   set_name("halberd");
   set_adj("black");
   set_short("black halberd");
   set_long("A wicked halberd, fashioned of a black alloy.\n");
   set_hit(34);
   set_pen(30);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE | W_SLASH);
   /*    add_prop(OBJ_I_VALUE, comp_value(30)); */
}
