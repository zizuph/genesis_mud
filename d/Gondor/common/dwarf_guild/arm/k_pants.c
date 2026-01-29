/*
 * /d/Gondor/common/dwarf_guild/arm/k_pants.c
 *
 * These pants are worn by the shopkeeper in the dwarven race guild. They
 * are secured on the inside, making them very nice armour
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

#define ARMOUR_CLASS 19

void
create_armour()
{
    set_name("pants");
    add_name("greaves");
    add_name("leggings");

    set_pname("pants");
    add_pname("greaves");
    add_pname("leggings");
    add_pname("armours");

    set_adj("comfortable");
    add_adj("ringed");
    add_adj("pair");
    add_adj("of");

    set_short("pair of comfortable pants");
    set_pshort("pairs of comfortable pants");

    set_long(BSN("These pants look very comfortable from the outside, " +
        "however looking at the inside you see that it is lined with a " +
        "special lining, which consists of small metal rings, making them " +
        "a pair of greaves rather the a normal pair of pants."));

    add_item( ({ "rings", "metal rings", "small rings", "small metal rings" }),
        BSN("The small metal rings make these pants into a strong pair of " +
        "greaves."));

    set_ac(ARMOUR_CLASS);
    set_at(A_LEGS);
    set_am( ({ -1, 2, -1 }) );

    add_prop(OBJ_I_WEIGHT, 4300);
    add_prop(OBJ_I_VOLUME, 3000);
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