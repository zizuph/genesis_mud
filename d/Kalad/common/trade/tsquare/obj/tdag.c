inherit "/d/Kalad/std/weapon.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("dagger");
   set_adj("keen");
   set_long("This is a sharp dagger, that closely resembles the "
	+"ones used by the guards. This one is not as clean, though "
	+"and is covered in bloodstains.\n");
   set_hit(20);
   set_pen(20);
   set_wt(W_KNIFE);
   set_dt(W_IMPALE);
   add_prop(OBJ_I_VALUE,300);
   add_prop(OBJ_I_WEIGHT,1500);
   add_prop(OBJ_I_VOLUME,1500);
}
