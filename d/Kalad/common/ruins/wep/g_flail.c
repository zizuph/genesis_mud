inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
create_weapon()
{
   ::create_weapon();
   set_name("flail");
   set_adj("spiked","large");
   set_long("This flail has a large spiked head and looks capable of "
	+"inflicting massive amounts of damage. It is issued to common "
	+"guardsmen to use on there rounds.\n");
   set_hit(28);
   set_pen(20);
   set_hands(W_ANYH);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_WEIGHT,9000);
   add_prop(OBJ_I_VOLUME,11000);
}
