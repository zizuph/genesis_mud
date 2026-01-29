inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
create_weapon()
{
   ::create_weapon();
   set_name("sword");
   set_adj("long","black");
   set_long("This sword is of average quality and in capable hands "
	+"could do average damage. It is common in the areas around "
	+"Zhentil Keep.\n");
   set_hit(25);
   set_pen(25);
   set_hands(W_ANYH);
   set_wt(W_SWORD);
   set_dt(W_IMPALE | W_SLASH);
   add_prop(OBJ_I_WEIGHT,9000);
   add_prop(OBJ_I_VOLUME,11000);
}
