inherit "/std/armour";

#include <formulas.h>		// F_VALUE_ARMOUR etc.
#include <stdproperties.h>	// OBJ_I_VALUE etc.
#include <wa_types.h>		// A_BODY

#include "examples.h"

void
create_armour()
{
    set_name("ringmail");
    add_name(({"mail", "doublet"}));
    set_adj(({"ring", "steel", "black", "leather"}));
    set_short("black ringmail");
    set_long("The mail is made from black steel rings sewn onto a "
      + "leather doublet.\n");

    // following 'man armour_guide'
    set_default_armour(17, A_BODY, ({-1,2,-1}));

    // randomize the value, values below F_VALUE_ARMOUR are impossible
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(17) + random(41));
    add_prop(OBJ_I_WEIGHT,
        F_WEIGHT_DEFAULT_ARMOUR(9, A_HEAD) + 50 - random(101));
    // iron has a density of 8g/cm^3, leather around 2g/cm^3
    // so equal parts leather and iron give 5g/cm^3 for the ringmail
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}

