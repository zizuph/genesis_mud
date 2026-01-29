/* This is a simple coat for the gnome children of Rust.
Created by Bishop of Calia, 28/10/98. */

inherit "/std/armour";

#include <wa_types.h>       
#include <formulas.h>      
#include <stdproperties.h>  
#include <macros.h>
#include "defs.h"

#define ARMOUR_CLASS 3

void
create_armour()
{
    set_name("coat");

    set_adj("light");
    set_adj("forest-green");

    set_short("light forest-green coat");
    set_pshort("forest-green coats");

    set_long("This little coat is made out thin leather that's" +
        " been dyed green, presumably to blend in better with the" +
        " forest. It's got short arms and would extend to the knees" +
        " of the average gnome child.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO);
    set_am(({ -1,2,-1 }));

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(50));

}
