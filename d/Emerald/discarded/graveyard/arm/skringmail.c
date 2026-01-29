 
/* graveyard/arm/skringmai.c  l is clone by graveyard/npc/skeleto_lord.c */
 
inherit "/std/armour";
 
#include <wa_types.h>
#include <formulas.h>
#include "/d/Emerald/defs.h"
 
 
void
create_armour()
{
 
    if(!IS_CLONE)
        return;
 
    set_name("ringmail");
    set_long( "It's a set of ringmail that covers "+
        "your body.\n" );
    set_adj("heavy");
    set_ac(16);
 
    set_am(({-1,2,-1}));
    set_at(A_BODY);
 
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(16));
}
