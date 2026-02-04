inherit "/std/weapon";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

#include "/d/Terel/common/terel_std_rec.h"
void
create_weapon()
{
  set_name("hatchet");
  set_long("A small hatchet to chop sticks with. In a pinch it could "+
           "probably be used as a weapon.\n");
 set_adj("small");
  set_hit(8);
  set_pen(7);

  set_wt(W_AXE); 
  set_dt(W_SLASH); 

  /* Last, how shall it be wielded? */
  set_hands(W_ANYH);

  add_prop(OBJ_I_WEIGHT, 1000);
  add_prop(OBJ_I_VOLUME, 1000);
}
