/* /d/Emerald/thief_lair/wep/bandit_broadsword.c

   Broadsword employed by the bandits of the Blackwall mountains.
   Such weapons were stolen from elvish patrols.
   - Casimir, 1999.
*/

inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("broadsword");
    add_name("sword");
    set_short("worn elvish broadsword");
    add_adj( ({"worn", "elvish"}) );
    set_long("This is a decent quality blade, clearly of elven make. "+
	     "Examining the weapon, you suspect that it was probabably "+
	     "acquired from an elf soldier.\n");

    set_hit(24);
    set_pen(23);
    set_wt(W_SWORD);
    set_dt(W_IMPALE|W_SLASH); 
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 6200);
    add_prop(OBJ_I_VOLUME, 4500);    
}
