inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
create_weapon()
{
   ::create_weapon();
   set_name("halberd");
   add_name("drowwep");
   set_adj("black");
   set_long("This weapon is crafted from some strange glowing alloy. "
	+"It's black blade is easily the size of a small shield and "
	+"is outlined in a pale blue glow, obviously some perverse drow "
	+"magic. The shaft of the halberd is made of metal also, but "
	+"remains extremely lightweight.\n");
   set_hit(35);
   set_pen(40);
   set_hands(W_BOTH);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE | W_SLASH);
   add_prop(OBJ_I_WEIGHT,9000);
   add_prop(OBJ_I_VOLUME,11000);
}
