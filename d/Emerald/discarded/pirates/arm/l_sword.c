/* This weapon is cloned by /d/Emerald/pirates/npc/pirate3
*/
inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

void
create_weapon()
{
   set_name("sword");
   set_adj("light");
   add_adj("long");
   set_short("light long sword");
   set_long("This sword looks well forged. It should last quite a while in " +
            "combat.\n");
   
   set_hit(18);
   set_pen(25);
   set_wt(W_SWORD);
   set_dt(W_IMPALE);
   
   set_hands(W_ANYH);
   
   
   add_prop(OBJ_I_VOLUME,1250);
   add_prop(OBJ_I_WEIGHT,4000);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(18,25)+random(200));
}
