inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("sword");
   set_adj("broad");
   set_adj("curved");
   set_long("This single-edged weapon is under three " +
      "feet in length and bears a slight curve.  Though made " +
      "of steel it holds a relatively unsharp edge.\n");
   set_hit(17);
   set_pen(16);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   set_hands(W_ANYH);
}
string
query_recover() {
   return MASTER + ":" + query_wep_recover();
}
void
init_recover(string arg) {
   init_wep_recover(arg);
}
