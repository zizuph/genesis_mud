/*  
 * Standard Haradrim sandals from Harondor.
 *  Serif, June 2001.
 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("pair of sandals");
    add_name("sandals");
    add_name("straps");
    set_pname("pairs");
    add_pname("pairs of sandals");
    add_adj("leather");
    add_adj("black");
    set_short("pair of black leather sandals");
    set_pshort("pairs of black leather sandals");
    set_long("Worn sandals made of strips of black leather carefully "
        + "woven together. The straps continue up the ankle and secure "
        + "around the calf and knee, providing a bit of protection to "
        + "the ankles as well as the feet. They seem like they would be "
        + "comfortable for traveling in warm areas, allowing ventalation "
        + "between the straps.\n");

    set_default_armour(8, (A_LEGS | A_ANKLES | A_FEET), ({ 0, 0, 0 }), 0);

    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 400); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8)+random(50)-25);
}
