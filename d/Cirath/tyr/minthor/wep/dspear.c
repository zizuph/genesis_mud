inherit "/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "defs.h"
create_weapon()
{
   ::create_weapon();
   set_name("spear");
   add_name("polearm");
   set_adj("double");
   set_short("double spear");
   set_long("This weapon is a wicked example of Athasian craftsmanship. "
	+"It is as tall as an elf, and on each end is an obsidian "
	+"spearhead.\n");
   set_hit(30);
   set_pen(30);
   set_hands(W_BOTH);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE);
   add_prop(OBJ_I_WEIGHT,900);
   add_prop(OBJ_I_VOLUME,900);
}
