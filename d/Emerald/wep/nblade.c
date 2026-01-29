inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
    set_name("blade");
    add_name("sword");
        set_short("night blade");
        set_long(break_string("This dark obsidian blade is as keen as the "+
                "day it was forged from volcanic rock. You feel a presence "+
                "within the blade as you wield it, alien and dark.\n", 76));
    set_adj("night");

    set_default_weapon(29, 33, W_SWORD, W_SLASH | W_IMPALE,  
         W_ANYH,  0);
    add_prop(OBJ_I_WEIGHT, 4700); 
    add_prop(OBJ_I_VOLUME,  860); 
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(29, 43) + random(10) - 140);

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
