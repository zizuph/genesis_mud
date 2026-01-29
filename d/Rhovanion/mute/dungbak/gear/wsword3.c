inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("sword");
   set_adj("two-handed");
   set_adj("copper");
   set_long("The pommel, hilt, and blade of this weapon " +
      "are constructed of well-polished copper;  quite " +
      "ornately designed on the pommel and hilt.  The " +
      "handle is thinly wrapped with some sort of grey " +
      "hide.\n");
   set_hit(15);
   set_pen(25);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   set_hands(W_BOTH);
}
string
query_recover() {
   return MASTER + ":" + query_wep_recover();
}
void
init_recover(string arg) {
   init_wep_recover(arg);
}
