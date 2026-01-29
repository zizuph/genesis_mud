inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
  set_name("club");
  set_short("iron club");
  set_long("This club looks nice to crush someone's head with. It has "+
           "old stains of blood on it and is rather filthy.\n");

  set_adj("iron");

  set_hit(27);
  set_pen(27);

  set_wt(W_CLUB);
  set_dt(W_BLUDGEON | W_SLASH); 

  set_hands(W_ANYH);

  add_prop(OBJ_I_WEIGHT, 4000);
  add_prop(OBJ_I_VOLUME, 2500);
}
