inherit "/std/armour";

#include <formulas.h>		// F_VALUE_ARMOUR etc.
#include <stdproperties.h>	// OBJ_I_VALUE etc.
#include <wa_types.h>		// A_HEAD

#include "examples.h"

void
create_armour()
{
    set_name("helmet");
    set_adj(({"studded", "leather"}));
    set_long("The helmet is made from a hard leath cap into which "
      + "metal studs have been set.\n");

    // following 'man armour_guide'
    set_default_armour(9, A_HEAD, ({0,1,-1}));

    // randomize the value, values below F_VALUE_ARMOUR are impossible
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(9) + random(21));
    add_prop(OBJ_I_WEIGHT,
        F_WEIGHT_DEFAULT_ARMOUR(9, A_HEAD) + 50 - random(101));
    // iron has a density of 8g/cm^3, leather around 2g/cm^3
    // so 2 parts leather and one part iron gives 4g/cm^3 for the helmet
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}

