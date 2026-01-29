inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("warhammer");
   set_adj("double-headed");
   set_adj("light");
   set_long("This weapon consists of a lightweight " +
      "wooden handle with carved grip and is topped with a " +
      "double-sided iron head for ease of use in battle.\n");
   set_hit(12);
   set_pen(10);
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
