inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_armour()
{
        set_name("cloak");
        set_short("cloak");
        set_long("Just some simple armour, not very useful.\n");
        set_ac(3);
        set_at(A_BODY);
        set_am(({       0,      0,      1 }));
        add_prop(OBJ_I_WEIGHT, 350); 
        add_prop(OBJ_I_VOLUME,  157); 
        add_prop(OBJ_I_VALUE, 30);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}
