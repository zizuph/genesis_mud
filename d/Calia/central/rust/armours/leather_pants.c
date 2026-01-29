/* These are simple pants for the gnome men of Rust
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
    set_name("pants");

    set_adj("brown");
    set_adj("leather");

    set_short("brown leather pants");
    set_pshort("leather pants");

    set_long("These leather pants would fit a gnome well. They're" +
        " warm and comfortable, but wouldn't offer much combat" +
        " protection.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_LEGS);
    set_am(({ -1,2,-1 }));

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(50));

}