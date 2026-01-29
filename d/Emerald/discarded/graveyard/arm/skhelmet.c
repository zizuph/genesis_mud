 
/* graveyard/arm/skhelmet.c  is clone by graveyard/npc/skeleto_lord.c */
 
inherit "/std/armour";
 
#include <wa_types.h>
#include <formulas.h>
#include "/d/Emerald/defs.h"
 
 
void
create_armour()
{
 
    if(!IS_CLONE)
        return;
 
    set_name("helmet");
    set_long( "A somewhat beaten and dented bronze helmet.\n" );
    set_adj("bronze");
    set_ac(18);
 
    set_at(A_HEAD);
 
    add_prop(OBJ_I_VOLUME,2200);
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(18));
}
