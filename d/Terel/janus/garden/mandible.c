inherit "/std/weapon";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Terel/common/terel_std_rec.h"

void
create_weapon()
{
  set_short("long mandible");
  set_name("mandible");
  set_long("The lower part of a warrior bugs mandible. It can be wielded as"+
           " a club.\n");
  set_adj("long");
  set_hit(10);
  set_pen(30);

  set_wt(W_CLUB); 
  set_dt(W_BLUDGEON); 

  /* Last, how shall it be wielded? */
  set_hands(W_ANYH);

  add_prop(OBJ_I_WEIGHT, 3000);
  add_prop(OBJ_I_VOLUME, 2000);
}
