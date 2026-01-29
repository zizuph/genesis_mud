inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("axe");
   set_adj("steel");
   set_adj("spear-tipped");
   set_long("This fine weapon bears a sharp, steel axe blade in " +
      "its front and tapers to a sharp point in its rear.  In addition " +
      "to its blades, a sharp spear tip protrudes from above the " +
      "blades constructed of the same steel shaft that is the " +
      "weapon's handle.  The handle itself is wrapped in some " +
      "kind of hide and provides a good grip.\n");
   set_hit(23);
   set_pen(25);
   set_wt(W_AXE);
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
