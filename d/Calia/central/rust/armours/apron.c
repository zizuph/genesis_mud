/* This is a simple apron for the gnome housewifes of Rust
Created by Bishop of Calia, 28/10/98. */

inherit "/std/armour";

#include <wa_types.h>       
#include <formulas.h>      
#include <stdproperties.h>  
#include <macros.h>
#include "defs.h"

#define ARMOUR_CLASS 4

void
create_armour()
{
    set_name("apron");

    set_adj("striped");
    set_adj("clean");

    set_short("striped clean apron");
    set_pshort("striped aprons");

    set_long("This neat apron looks like it would offer some protection." +
        " At least against stains when cooking.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO);
    set_am(({ -1,2,-1 }));

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(30));

}