inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
    set_name("axe");
    set_short("metal axe");
    set_long(break_string("This is a pretty plain metal axe.\n",76));
    set_adj("metal");

    set_default_weapon(14, 14, W_AXE, W_SLASH | W_BLUDGEON,  
         W_LEFT,  0);
    add_prop(OBJ_I_WEIGHT, 1500); 
    add_prop(OBJ_I_VOLUME,  495); 
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(14, 14) + random(5) - 90);
 }

string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}
