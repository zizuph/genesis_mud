/*
 * Leather vest - level 2
 * - Boreaulam, Sep 2012
 */
inherit "/std/armour";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

/*
 * Function name:        create_armour
 * Description  :        constructor for the object
 */
void
create_armour()
{

    set_name("vest");
    set_short("leather vest");
    set_adj("leather");
    set_long("This rough vest has been crudely fashioned from thick " +
        "leather. While the material appears tough enough, the cut fits " +
        "so poorly that you doubt the vest will provide much protection.\n");
    
    set_ac(10 + random(5));
    set_at(A_TORSO);

    add_prop(OBJ_I_VALUE, 250);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 3000);
} /* create_armour */