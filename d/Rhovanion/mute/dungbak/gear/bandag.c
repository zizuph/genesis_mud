inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   
   set_name("dagger");
   set_adj("serrated");
   set_long("The blade of this weapon curves back and forth " +
      "all along the blade giving it the property of serratedness. " +
      "It's pretty sharp and looks like you could really gut some body " +
      "with it.\n");
   set_hit(18);
   set_pen(22);
   set_wt(W_KNIFE);
   set_dt(W_SLASH | W_IMPALE);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT, 1000);
   add_prop(OBJ_I_VOLUME,  500);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(18, 22));
}
string
query_recover() {
   return MASTER + ":" + query_wep_recover();
}
void
init_recover(string arg) {
   init_wep_recover(arg);
}
