/*
 * /d/Gondor/common/dwarf_guild/arm/k_cloak.c
 *
 * This cloak is worn by the shopkeeper in the dwarven race guild.
 *
 * /Mercade, 3 august 1993
 *
 * Revision history:
 */

#pragma save_binary

inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

#define ARMOUR_CLASS 8

void
create_armour()
{
    set_name("mantle");
    add_name("cloak");

    set_pname("mantles");
    add_pname("cloaks");

    set_adj("smooth");
    add_adj("wool");

    set_short("smooth mantle");
    set_pshort("smooth mantles");

    set_long(BSN("This mantle is made of wool. It is woven very smoothly " +
        "which makes it very comfortable."));

    set_ac(ARMOUR_CLASS);
    set_at(A_ROBE);
    set_am( ({ 1, 1, -2 }) );

    add_prop(OBJ_I_WEIGHT, 1300);
    add_prop(OBJ_I_VOLUME, 1300);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(151) - 75);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}