/* This is a simple jacket for the gnome men of Rust
Created by Bishop of Calia, 28/10/98. */

inherit "/std/armour";

#include <wa_types.h>       
#include <formulas.h>      
#include <stdproperties.h>  
#include <macros.h>
#include "defs.h"

#define ARMOUR_CLASS 8

void
create_armour()
{
    set_name("jacket");

    set_adj("brown");
    set_adj("leather");

    set_short("brown leather jacket");
    set_pshort("leather jackets");

    set_long("This leather jacket looks in well crafted. While not" +
        " offering much protection against a blade, it would keep" +
        " you warm on a cold day.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO);
    set_am(({ -1,2,-1 }));

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(50));

}