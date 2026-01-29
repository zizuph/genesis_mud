/*
 * waterdeep/armour/g_helm.c
 * Helm worn by soldiers of the City Guard of Waterdeep
 *
 * Created by Brine, Feb 2021
 */

#pragma strict_types

#include "../defs.h"

inherit WATERDEEP_ARM;

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

#define AC          28
#define A_MOD       ({ 1, 1, -2 })
#define TYPE        A_HEAD

void
create_waterdeep_armour()
{
    set_name(({ "helm", "helmet", "skullcap", "skull-cap" }));
    set_adj(({ "polished", "steel" }));

    set_short("polished steel helm");
    set_long(
        CAP(LANG_ADDART(short())) + ". It is a skull-cap shaped from a single "
        + "sheet of steel. The rims angled outwards along the back and sides "
        + "to deflect blows away from the neck, and a strip of metal tapers "
        + "down from the front to form a nose-guard. It has been polished to "
        + "a shine. It looks masterfully crafted.\n"
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
        ({ "rim", "rims" }),
        "The rims of the " + short() + " are angled outwards along the sides "
        + "and back of the helm, to deflect blows away from the neck of the "
        + "wearer. It adds some stylish flair, too!\n"
    );

    add_item(
        ({
            "noseguard", "nose-guard", "nose guard", "strip", "strip of metal"
        }),
        "The nose-guard protects the face from glancing blows, without "
        + "obscuring the wearer's vision too badly.\n"
    );
}
