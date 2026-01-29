inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("warhammer");
   set_adj("steel-headed");
   set_adj("hefty");
   set_long("This hammer consists of a stout wooden handle " +
      "and a well-designed steel head.  It looks like it " +
      "could do some damage.\n");
   set_hit(15);
   set_pen(20);
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
