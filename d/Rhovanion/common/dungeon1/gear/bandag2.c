inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("knife");
   set_adj("wide");
   set_adj("long");
   set_long("This is a wide-bladed, long knife of no " +
      "extraordinary value.  It serves its purpose though despite " +
      "its humble appearance.\n");
   set_hit(14);
   set_pen(20);
   set_wt(W_KNIFE);
   set_dt(W_SLASH | W_IMPALE);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT, 1000);
   add_prop(OBJ_I_VOLUME,  500);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(14,20));
}
string
query_recover() {
   return MASTER + ":" + query_wep_recover();
}
void
init_recover(string arg) {
   init_wep_recover(arg);
}
