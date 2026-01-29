/* /d/Emerald/thief_lair/wep/bandit_club.c

   A weapon used by the bandits of the Blackwall mountains.
   - Casimir, 1999.
*/

inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("club");
    set_short("crude spiked club");
    add_adj( ({"crude", "spiked"}) );
    set_long("A stout piece of wood through which iron nails "+
	     "have been driven to turn it into a fearsome "+
	     "looking weapon.\n");

    set_hit(22);
    set_pen(20);
    likely_dull = 5;
    likely_break = 13;

    set_wt(W_CLUB);
    set_dt(W_IMPALE|W_BLUDGEON); 
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 7900);
    add_prop(OBJ_I_VOLUME, 6200);    
}

