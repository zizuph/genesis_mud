/* 	iron boots for the young knight in the crystalline palace

    coder(s):   Glykron

    history:    17.11.94    A_LEGS -> A_FEET                Maniac
                25. 2.92    recovery added                  Glykron
                25. 2.92    header added                    Glykron

*/

#pragma save_binary

inherit "/std/armour.c";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_armour()
{
    set_name( ({ "pair", "boots" }) );
    set_pname( ({ "pairs", "boots" }) );
    set_adj("iron");
    set_short("pair of iron boots");
    set_pshort("pairs of iron boots");
    set_long("These are comfortable iron boots.\n");
    set_ac(15);
    set_at(A_FEET);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 3000);
}