/*
 *	/d/Gondor/common/arm/herb_gloves.c
 *
 *	Copied from /d/Krynn/common/armours/herb_gloves.c
 *	Herbalist's gloves by Teth Jan 22 1997
 *
 *	Olorin, 30-Jun-1997
 */
#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("gloves");
    add_name(({"armour","pair of gloves"}));
    add_name("glove");
    set_pname("gloves");
    add_pname(({"armours", "pairs of gloves"}));
    set_adj("leather");
    set_short("pair of herbalist's gloves");
    set_pshort("pairs of herbalist's gloves");
    set_long("This pair of gloves is merely for protection against " +
        "the various contact poisons a herbalist may find while " +
        "collecting plants. The pair of gloves offers no protection against " +
        "blunt attacks on the hands, and a little protection against " +
        "slashing and impaling weapons.\n");
    set_adj("herbalist's");
    set_ac(1);
    set_am(({0, 1, -1}));
    set_at(A_HANDS);
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 12 * (F_VALUE_ARMOUR(1) / 12 + 1));
    
    add_prop("_obj_i_ignore_recovery", 1);
}

