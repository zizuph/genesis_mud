 
/* graveyard/arm/skshield.c  is clone by graveyard/npc/skeleto_lord.c */
 
inherit "/std/armour";
 
#include "/d/Emerald/defs.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
 
 
void
create_armour()
{
 
    if(!IS_CLONE)
        return;
 
    set_name("shield");
    set_long( "A small shield made from wood, with reinforcing "+
        "strips of metal.\n" );
    set_adj(({"small","wooden"}));
    set_ac(11);
 
    set_at(A_SHIELD);
 
    add_prop(OBJ_I_VOLUME,1100);
    add_prop(OBJ_I_WEIGHT,1200);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(11) - random(30));
}
 
