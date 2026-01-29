inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("axe");
   set_adj("iron");
   set_adj("black");
   set_long("Though this dull black, iron axe be far " +
      "from razor sharp, its weight and build might allow " +
      "its edge to do a bit of smashing damage.\n");
   set_hit(10);
   set_pen(15);
   set_wt(W_AXE);
   set_dt(W_SLASH | W_BLUDGEON);
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
