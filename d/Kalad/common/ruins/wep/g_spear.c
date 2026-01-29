inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
create_weapon()
{
   ::create_weapon();
   set_name("spear");
   set_adj("long","sharp");
   set_long("This is an average spear of the guardsmen in Zhentil Keep. "
	+"It has a long haft, and a razor-sharp head.\n");
   set_hit(28);
   set_pen(33);
   set_hands(W_ANYH);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE);
   add_prop(OBJ_I_WEIGHT,9000);
   add_prop(OBJ_I_VOLUME,11000);
}
