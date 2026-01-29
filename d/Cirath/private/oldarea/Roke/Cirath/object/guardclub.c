inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
  set_name("club");
  set_long("This club looks nasty. You could propably "+
           "bonk a horse to unconciousness easily with it.\n");

  set_adj("brutal");
  add_adj("brain-beating");

  set_hit(35);
  set_pen(35);

  set_wt(W_CLUB);
  set_dt(W_BLUDGEON | W_SLASH); 

  set_hands(W_RIGHT);

  add_prop(OBJ_I_WEIGHT, 5000);
  add_prop(OBJ_I_VOLUME, 2500);
}
