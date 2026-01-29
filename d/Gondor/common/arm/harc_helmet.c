/*
 * Helmet worn by the haradrim captains
 * -- Finwe, July 2005
 */

inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name(({"helmet"}));
    set_pname("helmets");
    set_short("steel plate helmet");
    set_pshort("steel plate helmets");
    set_adj(({"steel", "plate",}));
    set_long("This is a steel plate helmet. It is made from plates of steel " +
        "hammered together. It is a common helmet worn by the Captains " +
        "of the Haradrim\n");
    set_default_armour(25,A_HEAD,({-1,1,0}),0);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25) * (120 - random(21)) / 100);
    add_prop(OBJ_I_WEIGHT,2400);
    add_prop(OBJ_I_VOLUME,1200);

}

