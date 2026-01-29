inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
create_weapon()
{
   ::create_weapon();
   set_name("halberd");
   set_adj("steel","black");
   set_long("This halberd is standard issue to the troops in Zhentil "
	+"Keep. It has a black steel head, and a long wooden handle.\n");
   set_hit(30);
   set_pen(35);
   set_hands(W_BOTH);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE | W_SLASH);
   add_prop(OBJ_I_WEIGHT,9000);
   add_prop(OBJ_I_VOLUME,11000);
}
