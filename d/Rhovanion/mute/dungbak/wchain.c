inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("chain");
   set_adj("iron");
   set_adj("weighted");
   set_long("This is an iron chain about ten feet in length " +
      "with links of about an inch and a half in length.  The " +
      "ends are weighted with five inch iron balls studded with " +
      "steel studs leading you to assume this weapon, in the " +
      "hands of an experienced wielder, could do some damage.\n");
   set_hit(20);
   set_pen(30);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
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
