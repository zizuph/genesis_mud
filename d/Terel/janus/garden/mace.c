inherit "/std/weapon";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Terel/common/terel_std_rec.h"

void
create_weapon()
{
  set_name("mace");
  set_long("A heavy well balanced steel mace.\n");
  set_adj(({"steel","heavy","balanced"}));
  set_hit(20);
  set_pen(25);

  set_wt(W_CLUB); 
  set_dt(W_BLUDGEON); 

  /* Last, how shall it be wielded? */
  set_hands(W_ANYH);

  add_prop(OBJ_I_WEIGHT, 5000);
  add_prop(OBJ_I_VOLUME, 4000);
}
