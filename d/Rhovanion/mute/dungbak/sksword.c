inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("sword");
   set_adj("rusty");
   set_long("This longsword is covered in rust.  The hilt is " +
      "also a bit loose.\n");
   set_hit(7);
   set_pen(10);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   set_hands(W_ANYH);
   set_dull(4);
}
string
query_recover() {
   return MASTER + ":" + query_wep_recover();
}
void
init_recover(string arg) {
   init_wep_recover(arg);
}
