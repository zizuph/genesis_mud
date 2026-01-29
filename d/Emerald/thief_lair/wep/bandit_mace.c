/* ~Emerald/thief_lair/wep/bandit_mace.c

   A weapon commonly employed by the bandits of the Blackwall mountains.
   It was stolen from the local elves, of course.
   - Casimir, 1999.
*/

inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("mace");
    add_name("club");
    set_short("worn elvish mace");
    add_adj( ({"worn", "elvish"}) );
    set_long("A well-used mace footman's mace, clearly of elvish "+
	     "manufacture. It seems likely that it was acquired from "+
	     "an elven soldier.\n");
    set_hit(29);
    set_pen(23);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 5800);
    add_prop(OBJ_I_VOLUME, 3200);
}
