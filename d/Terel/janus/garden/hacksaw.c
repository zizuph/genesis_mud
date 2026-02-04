inherit "/std/weapon";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

#include "/d/Terel/common/terel_std_rec.h"
void
create_weapon()
{
  set_name("hacksaw");
  set_long(break_string("A small hacksaw. Useful for cutting branches, but "+
      "not so useful in combat. Unless your opponent is sitting "+
      "on a branch. \n",70));
 set_adj("small");
  set_hit(2);
  set_pen(3);

  set_wt(W_SWORD); 
  set_dt(W_SLASH); 

  /* Last, how shall it be wielded? */
  set_hands(W_ANYH);

  add_prop(OBJ_I_WEIGHT, 1000);
  add_prop(OBJ_I_VOLUME, 1000);
}
