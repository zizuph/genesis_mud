/* mine/arm/jerkin.c id cloned by mine/npc/miner.c */
 
inherit "/std/armour";

#pragma save_binary
#include <stdproperties.h>
#include <wa_types.h>
 
void
create_armour()
{
    set_name("jerkin");
    set_short("leather jerkin");
    set_long("Just some simple leather armor, not very useful.\n");
    set_adj("leather");
    set_ac(3);
    set_at(A_BODY);
    set_am(({       0,      0,      1 }));
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME,  157);
    add_prop(OBJ_I_VALUE, 30);
}
 
