inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("sword");
   set_adj("mist");
   set_adj("vaporous");
   set_long("You shouldn't have this!");
   set_hit(25);
   set_pen(20);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   set_hands(W_BOTH);
}
