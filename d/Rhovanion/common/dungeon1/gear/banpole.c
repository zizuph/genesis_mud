inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("pole axe");
   set_long("This two handed weapon looks dangerous and very " +
      "imposing.  It consists of a long wooden pole about eight " +
      "feet in length with a hastily attached blade on the end.  The " +
      "blade is double-sided and similar in appearance to an axe blade.\n");
   set_hit(25);
   set_pen(25);
   set_wt(W_POLEARM);
   set_dt(W_SLASH | W_BLUDGEON);
   set_hands(W_BOTH);
   add_prop(OBJ_I_WEIGHT, 10000);
   add_prop(OBJ_I_VOLUME, 5000);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(25,25));
}
string
query_recover() {
   return MASTER + ":" + query_wep_recover();
}
void
init_recover(string arg) {
   init_wep_recover(arg);
}
