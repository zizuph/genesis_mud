inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("blade");
   set_adj("handle-less");
   set_long("This is the unhandled blade of a newly " +
      "hammered knife.  It's been sharpened pretty well, " +
      "but without a handle it just isn't as effective.\n");
   set_hit(9);
   set_pen(12);
   set_wt(W_KNIFE);
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
