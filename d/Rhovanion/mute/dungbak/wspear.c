inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("spear");
   set_adj("bladed");
   set_adj("long");
   set_long("This weapon consists of a long, hardwood " +
      "shaft set at its head with, instead of a simple " +
      "spear head, a long, curved blade.  A red tassle " +
      "hangs from just below the blade, and the bottom " +
      "of the shaft is fitted with an iron ball for a " +
      "counterweight so the weapon may be swung more " +
      "effectively for greater damage.\n");
   set_hit(24);
   set_pen(30);
   set_wt(W_POLEARM);
   set_dt(W_SLASH | W_IMPALE);
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
