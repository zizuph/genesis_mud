inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("spear");
   set_adj("rusted");
   set_adj("short");
   set_long("The end of this spear looks as if it were " +
      "broken off shortening the effective length of the " +
      "weapon to about 5 feet or so.  The spear head itself " +
      "has been seriously rusted.\n");
   set_hit(7);
   set_pen(9);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE);
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
