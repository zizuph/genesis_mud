 
/* mine/wep/paxe.c is cloned by mine/npc/miner.c */
 
inherit "/std/weapon";

#pragma save_binary 
#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
 
void
create_weapon()
{
    set_name("axe");
    add_name("_mylos_quest_axe_");
    set_short("pick axe");
    set_long( "This is a dingy old pick axe.\n" );
    set_adj("pick");
 
    set_default_weapon(8, 8, W_AXE, W_BLUDGEON,
                       W_RIGHT,  0);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME,  343);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(8, 8) + random(5) - 100);
}
 
