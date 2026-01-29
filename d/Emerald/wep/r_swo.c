inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
    set_name("sword");
    set_short("ranger sword");
    set_long(break_string("This sword is a fairly well made sword, but nothing "+
		"special to say the least.\n",76));
    set_adj("ranger");

    set_default_weapon(20, 23, W_SWORD, W_SLASH | W_IMPALE,  
         W_RIGHT,  0);
    add_prop(OBJ_I_WEIGHT, 2080); 
    add_prop(OBJ_I_VOLUME,  860); 
    add_prop(OBJ_I_VALUE, 700);
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
