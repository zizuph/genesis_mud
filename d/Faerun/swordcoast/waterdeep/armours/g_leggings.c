/*
 * waterdeep/armour/g_leggings.c
 * Leggings worn by soldiers of the City Guard of Waterdeep
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
#define A_MOD       ({ -2, 1, 1 })
#define TYPE        A_LEGS

void
create_waterdeep_armour()
{
    set_name(({ "leggings", "pair of leggings" }));
    set_pname("pairs of leggings");
    set_adj(({ "padded", "steel" }));

    set_short("pair of padded leggings with steel faulds");
    set_pshort("pairs of padded leggings with steel faulds");
    set_long(
        CAP(LANG_ADDART(short())) + ". They are three-layered garments, "
        + "consisting first of cloth leggings, then a thick, padded thigh-"
        + "length skirt, and finally of steel plated faulds to cover the "
        + "waist and upper thighs. These garments are tyically worn as part "
        + "of a half-plate armour. They look masterfully crafted.\n"
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
        "cloth leggings",
        "They are tight-fitting cloth leggings that protect the skin from "
        + "the elements, but not much else.\n"
    );

    add_item(
        ({ "skirt", "thick skirt", "padded skirt" }),
        "It is a skirt that goes to about right above the knees. It is made "
        + "from thick, padded cloth and looks to offer good protection.\n"
    );

    add_item(
        ({ "faulds", "steel faulds", "plated faulds", "steel plated faulds" }),
        "They are faulds made from steel plates. They run from the waist and "
        + "down to about mid-thigh. They are meant to be an extension to a "
        + "breastplate or similar body-armour, offering protection where the "
        + "body-armour ends.\n"
    );
}
