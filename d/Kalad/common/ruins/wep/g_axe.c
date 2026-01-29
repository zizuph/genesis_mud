inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
create_weapon()
{
   ::create_weapon();
   set_name("axe");
   set_adj("short-hafted","black-bladed");
   set_long("This is an axe of decent quality that is used by the city "
	+"guards of the Zhentil Keep. It has a broad head and a short "
	+"handle.\n");
   set_hit(23);
   set_pen(28);
   set_hands(W_ANYH);
   set_wt(W_AXE);
   set_dt(W_SLASH);
   add_prop(OBJ_I_WEIGHT,9000);
   add_prop(OBJ_I_VOLUME,11000);
}
