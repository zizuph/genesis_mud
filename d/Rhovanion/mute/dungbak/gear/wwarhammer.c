inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("warhammer");
   set_adj("iron-headed");
   set_adj("short");
   set_long("This small weapon consists of a short wooden " +
      "handle with a leather strapped grip and a " +
      "head of solid, black iron tapered to a sharp point " +
      "in its rear.\n");
   set_hit(10);
   set_pen(22);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
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
