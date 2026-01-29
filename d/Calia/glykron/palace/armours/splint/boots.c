/* 	splint boots for the training knight in the crystalline palace

    coder(s):   Glykron

    history:    25. 2.92    recovery added                  Glykron
                25. 2.92    header added                    Glykron

*/

#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name( ({ "pair", "boots" }) );
    set_pname( ({ "pairs", "boots" }) );
    set_adj("splint");
    set_short("pair of splint-plated boots");
    set_pshort("pairs of splint-plated boots");
    set_long("These splint-plated boots are of a human make.\n");
    set_ac(20);
    set_at(A_FEET);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 1500);
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