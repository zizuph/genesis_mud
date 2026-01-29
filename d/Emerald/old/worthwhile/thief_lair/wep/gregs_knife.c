/* /d/Emerald/thief_lair/wep/gregs_sword.c

   Gregarry, the lieutenant of the bandits, sword.
   - Casimir, 1999.
*/

inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <formulas.h>

void
create_weapon()
{
    set_name("dagger");
    set_short("long slender dagger");
    add_adj( ({"long", "slender"}) );
    set_long("The foot long blade on this ornately forged "+
	     "dagger suggests that it was designed with more "+
	     "than its ornamental value in mind. It handles "+
	     "superbly well in combat.\n");

    set_hit(20);
    set_pen(20);
    likely_dull = 9;
    likely_break = 9;
    likely_corr = 9;

    set_wt(W_KNIFE);
    set_dt(W_IMPALE); 
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 2150);
    add_prop(OBJ_I_VOLUME, 950); 
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20, 20) + random(200));
}

