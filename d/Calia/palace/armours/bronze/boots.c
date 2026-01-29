/* 	bronze boots for the bronze knight in the crystalline palace

    coder(s):   Glykron

    history:    25. 2.92    recovery added                  Glykron
                 9. 2.92    header added                    Glykron

*/

#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("boots");
    set_pname("boots");
    set_adj("bronze");
    set_short("pair of bronze boots");
    set_pshort("pairs of bronze boots");
    set_long("These bronze boots are of a dwarven make.\n");
    set_ac(12);
    set_at(A_FEET);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 3000);
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