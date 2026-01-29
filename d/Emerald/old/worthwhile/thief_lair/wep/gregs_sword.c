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
    set_name("sword");
    add_name("longsword");
    set_short("elegant longsword");
    add_adj( ({"elegant"}) );
    set_long("A fine weapon, likely of elvish craft. The blade "+
	     "of this longsword is atypically narrow, but very sharp. "+
	     "The weapon handles beautifully, and the relativly light "+
	     "weight makes it an ideal weapon to use in conjuction with "+
	     "another, should one be skilled in using two weapons at "+
	     "once.\n");

    set_hit(34);
    set_pen(30);
    likely_dull = 8;
    likely_break = 12;
    likely_corr = 10;

    set_wt(W_SWORD);
    set_dt(W_IMPALE|W_SLASH); 
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 5350);
    add_prop(OBJ_I_VOLUME, 2700);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(34, 20) + random(200));    
}

