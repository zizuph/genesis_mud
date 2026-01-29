inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("knife");
   set_adj("tin");
   set_adj("serrated");
   set_long("Though made of a crappy metal, the " +
      "jagged serrates on this blade prevent it from being " +
      "a total loss.\n");
   set_hit(15);
   set_pen(20);
   set_wt(W_KNIFE);
   set_dt(W_SLASH);
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
