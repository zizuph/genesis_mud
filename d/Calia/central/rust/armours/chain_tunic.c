/* This is a chain tunic for the guards of Rust. It's worn as a
robe over their banded mail. Made by Bishop of Calia,
11/11/98 */


inherit "/std/armour";

#include <wa_types.h>       
#include <formulas.h>      
#include <stdproperties.h>  
#include <macros.h>
#include "defs.h"

#define ARMOUR_CLASS 12

void
create_armour()
{
    set_name("tunic");

    set_adj("chain");

    set_short("chain tunic");
    set_pshort("chain tunics");

    set_long("This plain tunic is made out of hundreds of minute" +
        " rings that have been attached together. It is not very" +
        " sturdy in itself, and is probably intended to be worn over" +
        " another piece of armour.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_ROBE);
    set_am(({ -1,2,-1 }));

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(50));

}