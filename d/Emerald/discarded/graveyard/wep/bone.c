/* graveyard/wep/bone.c  is clone by graveyard/npc/zombie.c */
 
inherit "/std/weapon";
 
#include "/sys/wa_types.h"
#include "/d/Emerald/defs.h"
#include "/sys/formulas.h"
 
 
void
create_weapon()
{
 
    if(!IS_CLONE)
        return;
 
    set_name("bone");
    set_short("large bone");
    set_long("A large white bone, which probably could "+
        "be used as a rather basic club.\n");
    set_adj("large");
 
    set_hit(8);
    set_pen(11);
 
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
 
    set_hands(W_BOTH);
 
 
    add_prop(OBJ_I_VOLUME,2000);
    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(8,11));
}
 
