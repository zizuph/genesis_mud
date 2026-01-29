inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("club");
   set_adj("stick");
   set_long("This `weapon' is less so a weapon than " +
      "a branch or large stick.\n");
   set_hit(7);
   set_pen(11);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   set_hands(W_ANYH);
   set_dull(3);
}
string
query_recover() {
   return MASTER + ":" + query_wep_recover();
}
void
init_recover(string arg) {
   init_wep_recover(arg);
}
