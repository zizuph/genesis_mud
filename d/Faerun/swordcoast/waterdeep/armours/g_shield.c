/*
 * waterdeep/armour/g_shield.c
 * Shield worn by soldiers of the City Guard of Waterdeep
 *
 * Created by Brine, Feb 2021
 */

#pragma strict_types

#include "../defs.h"

inherit WATERDEEP_ARM;

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

#define AC          25
#define A_MOD       ({ 2, 1, -3 })
#define TYPE        A_SHIELD

void
create_waterdeep_armour()
{
    set_name(({ "shield", "heater", "heater shield" }));
    set_adj(({ "wooden", "plated" }));

    set_short("painted heater shield");
    set_long(
        CAP(LANG_ADDART(short())) + ". It is made from wood that has been "
        + "overlaid with hardened leather. Its flat top and tapered end gives "
        + "it a distinctive triangular shape. It is painted with the coat of "
        + "arms of Waterdeep, the City of Splendors. It looks masterfully "
        + "crafted.\n"
    );

    set_default_armour(AC, TYPE, A_MOD);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(AC));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, TYPE));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(
        OBJ_S_WIZINFO,
        "Armour worn by soldiers of the City Guard of Waterdeep.\n"
    );

    add_item(
        ({ "symbol", "coat", "coat of arms" }),
        "The " + short() + " is painted with the coat of arms of Waterdeep, a "
        + "crescent moon rising above sharp mountains, the sea below "
        + "reflecting the moon as well as 8 stars.\n"
    );

    add_item(
        ({
            "top", "flat top", "end", "tapered end", "shape", "triangular shape"
        }),
        "The " + short() + " has a flat top and tapers towards a single point "
        + "at the bottom, giving it the distinctive triangular shape that "
        + "give heater shields their name.\n"
    );

    add_item(
        ({
            "wood", "leather", "hardened leather"
        }),
        "The " + short() + " is made from wood that has been overlaid with "
        + "hardened leather, making it very tough and durable.\n"
    );
}
