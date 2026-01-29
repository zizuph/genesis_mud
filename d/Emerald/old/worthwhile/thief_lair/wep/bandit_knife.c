/* /d/Emerald/thief_lair/wep/bandit_knife.c

   A weapon used by the bandits of the Blackwall mountains.
   - Casimir, 1999.
*/

inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("knife");
    set_short("large serrated knife");
    add_adj( ({"large", "serrated"}) );
    set_long("A large hunting knife, with a serrated blade to "+
	     "improve its sawing ability, and, no doubt, the damage "+
	     "it would do to flesh.\n");

    set_hit(16);
    set_pen(17);
    set_wt(W_KNIFE);
    set_dt(W_SLASH); 
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 2100);
    add_prop(OBJ_I_VOLUME, 2300);    
}

