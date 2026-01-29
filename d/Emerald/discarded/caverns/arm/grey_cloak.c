inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_armour()
{
    set_name("cloak");
    set_long("This is a dirty, yet thick grey cloak.\n");
    set_adj("grey");
    set_ac(16);
    set_am( ({-2, 1, 1}) );
    set_at(A_ROBE);
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
