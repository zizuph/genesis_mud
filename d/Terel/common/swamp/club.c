inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon(){
   set_name("club");
   set_adj("spiked");
   set_short("spiked club");
   set_long("A wicked little spiked club.\n");
   set_hit(12);
   set_pen(15);
   set_wt(W_CLUB);
   set_dt(W_IMPALE);
}
