inherit "/std/weapon";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

#include "/d/Terel/common/terel_std_rec.h"
void
create_weapon()
{
  set_name("hammer");
  set_long("A small sturdy hammer, with a worn wooden handle. \n");
  set_adj(({"small","sturdy"}));
  set_hit(10);
  set_pen(5);

  set_wt(W_CLUB); 
  set_dt(W_BLUDGEON); 

  /* Last, how shall it be wielded? */
  set_hands(W_ANYH);

  add_prop(OBJ_I_WEIGHT, 1000);
  add_prop(OBJ_I_VOLUME, 1000);
}
