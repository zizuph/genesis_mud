inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("shortsword");
   add_name("sword");
   set_adj("hooked");
   set_long("This iron shortsword is about two feet in " +
      "length and bends slightly in the middle.  For some " +
      "warriors, this addition fits their style better.\n");
   set_hit(15);
   set_pen(15);
   set_wt(W_SWORD);
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
