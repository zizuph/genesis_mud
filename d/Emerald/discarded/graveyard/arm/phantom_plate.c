 
/* graveyard/arm/phantom_plate.c  is clone by graveyard/npc/phantom_knight.c */
 
inherit "/std/armour";
 
#include "/d/Emerald/defs.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
 
 
void
create_armour()
{
 
    if(!IS_CLONE)
        return;
 
    set_name("plate");
    set_short("phantom plate");
    set_long( "A thick black torso plate that looks like very "+
        "effective armour.\n" );
    set_adj("phantom");
    set_ac(40);
 
    set_am(({0,0,0}));  /*armour modifiers - slash,impale,bludgeon*/
    set_at(A_BODY);
 
    add_prop(OBJ_I_VOLUME,3000);
    add_prop(OBJ_I_WEIGHT,9200);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(40));
}
 
