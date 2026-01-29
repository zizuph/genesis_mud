/*
 * waterdeep/armour/g_boots.c
 * Boots worn by soldiers of the City Guard of Waterdeep
 *
 * Created by Brine, Feb 2021
 */

#pragma strict_types

#include "../defs.h"

inherit WATERDEEP_ARM;

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

#define AC          5
#define A_MOD       ({ 0, 1, -1 })
#define TYPE        A_FEET

void
create_waterdeep_armour()
{
    set_name(({ "boots", "pair of boots" }));
    set_pname("pairs of boots");
    set_adj(({ "tall", "leather" }));

    set_short("pair of tall leather boots");
    set_pshort("pairs of tall leather boots");
    set_long(
        CAP(LANG_ADDART(short())) + ". They are nearly knee-high, and made "
        + "from soft leather. A decorative buckle runs across each shin. They "
        + "are lined on the inside with sheep's wool, making them warm and "
        + "comfortable boots.\n"
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
        ({
            "buckle", "decorative buckle", "buckles", "decorative buckles",
            "band", "shaft"
        }),
        "A band runs around the shaft of each boot, with a buckle fastened to "
        + "it directly over the shin. It could be used to fasten the band, but "
        + "mostly serves as a decorative feature.\n"
    );
}
