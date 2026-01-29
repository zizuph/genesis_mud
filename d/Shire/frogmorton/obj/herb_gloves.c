/*
 *  Based on the herbalist's gloves of Gondor, which are in turn, 
 *  based on Teth's herbalist gloves in Krynn.
 *  -- Finwe, February 2002
 */
#pragma strict_types


inherit "/std/armour";
inherit "/lib/keep";

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("gloves");
    add_name(({"armour","pair of gloves"}));
    set_pname("gloves");
    add_pname(({"pairs of gloves"}));
    set_adj("leather");
    set_short("pair of leather herbing gloves");
    set_pshort("pairs of leather herbing gloves");
    set_long("This pair of gloves is made from thin, supple " +
        "leather. They are worn by herbalists to protect " +
        "their hands and fingers when gathering herbs in the wild. " +
        "The gloves, however, offer no protection in battles or " +
        "from weapons.\n");

    set_ac(1);
    set_am(({0, 1, -1}));
    set_at(A_HANDS);
    set_keep(1);

    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 12 * (F_VALUE_ARMOUR(1) / 12 + 1));
}

