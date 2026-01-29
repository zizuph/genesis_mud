/* township/wep/smith_wep.c is cloned by township/npc/blacksmith.c */
inherit "/std/weapon";
 
#include "/d/Emerald/defs.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
 
 
void
create_weapon()
{
 
    if(!IS_CLONE)
        return;
 
    set_name("hammer");
    set_short("heavy hammer");
    set_long("A heavy blacksmiths hammer. It's obviously not " +
        "meant to be used as a weapon, but it could still be used quite " +
        "effectively as one.\n");
    set_adj("heavy");
 
    set_hit(23);
    set_pen(26);
 
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
 
    set_hands(W_BOTH);
 
 
    add_prop(OBJ_I_VOLUME,400);
    add_prop(OBJ_I_WEIGHT,10000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(23,26) + random(90) - 45);
}
 
