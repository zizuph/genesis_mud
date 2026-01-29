

#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_armour()
{
    set_name("gloves");
    add_name("pair of gloves");
    add_name("_calia_hardware_shop_");
    set_pname("gloves");
    add_pname("pairs of gloves");
    set_adj("leather");
    set_short("pair of leather gloves");
    set_pshort("pairs of leather gloves");
    set_long("A small pair of leather gloves to protect your hands "+
        "while herbing in the various lands of the realms.\n");
    set_ac(1);
    set_am(({0,0,0}));
    set_at(A_HANDS);
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, 130);
    add_prop(OBJ_I_VOLUME, 185);
}

