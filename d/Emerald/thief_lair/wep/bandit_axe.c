/* /d/Emerald/thief_lair/wep/bandit_axe.c

   A weapon used by the bandits of the Blackwall mountains.
   - Casimir, 1999.
*/

inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("axe");
    set_short("large woodsman's axe");
    add_adj( ({"large", "woodman's"}) );
    set_long("A good-sized blade adorns what otherwise would be a "+
	     "device common to farmers and woodsmen. The larger "+
	     "blade suggests a more sinister purpose.\n");

    set_hit(16);
    set_pen(25);
    set_likely_break(12);

    set_wt(W_AXE);
    set_dt(W_SLASH|W_BLUDGEON); 
    set_hands(W_ANYH);

    
    add_prop(OBJ_I_WEIGHT, 7750);
    add_prop(OBJ_I_VOLUME, 5500);    
}

