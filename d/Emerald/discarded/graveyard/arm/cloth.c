 
/* graveyard/arm/cloth.c  is clone by graveyard/npc/zombie.c */
 
inherit "/std/armour";
 
#include "/d/Emerald/defs.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
 
 
void
create_armour()
{
 
    if(!IS_CLONE)
        return;
 
    set_name("cloth");
    set_short("tattered cloth");
    set_long("It's a tattered old piece of cloth, but "+
        "I suppose it's better than nothing.\n");
    set_adj("tattered");
    set_ac(3);
 
    set_am(({-1,1,0}));  /*armour modifiers - slash,impale,bludgeon*/
    set_at(A_BODY);
 
    add_prop(OBJ_I_VOLUME,200);
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(3));
}
