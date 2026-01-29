inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("robe");
    set_ac(3);
    set_at(A_ROBE);
    add_adj("small");
    set_long("It's made of soft and thick material, but yet it's not " +
	"very heavy.\n");
    add_prop(OBJ_I_VOLUME, 4750);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(3, A_ROBE));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3));
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

