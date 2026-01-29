/*
 * Farmer Pants
 * -- Finwe, November 2006
 */

inherit "/std/armour";

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("pants");
    set_short("pair of leather pants");
    add_adj("brown");
    add_adj("leather");
    set_long("This is a pair of leather pants. They are of dirty and well " +
        "worn. The leather pants look like the type that farmers and " +
        "commoners wear.\n");

    set_ac(8);
    set_am(({0,0,0,}));
    set_at(A_LEGS);
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 100);
}
