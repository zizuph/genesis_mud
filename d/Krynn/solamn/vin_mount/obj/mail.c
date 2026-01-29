inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("armour");
    set_ac(25);
    set_at(A_BODY);
    add_adj( ({ "black", "body" }) );
    set_long("In this piece of armour a draconian would feel safe.\n");
    add_prop(OBJ_I_VOLUME, 3040);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(25, A_BODY));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25));
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

