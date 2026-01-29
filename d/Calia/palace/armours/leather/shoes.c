/* 	leather shoes for the knight's son in the crystalline palace

    coder(s):   Glykron

    history:    25. 2.92    recovery added                  Glykron
                25. 2.92    header added                    Glykron

*/

#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_armour()
{
    set_name( ({ "pair", "shoes" }) );
    set_pname( ({ "pairs", "shoes" }) );
    set_adj("leather");
    set_short("pair of leather shoes");
    set_pshort("pairs of leather shoes");
    set_long("These are good leather shoes.\n");
    set_ac(10);
    set_at(A_FEET);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 2000);
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