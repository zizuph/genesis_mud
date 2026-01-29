/*
 * waterdeep/weapons/g_mace.c
 * A mace used by soldiers in the City Guard
 *
 * Created by Brine, Feb 2021
 */

#pragma strict_types

#include "../defs.h"

inherit WATERDEEP_WEP;

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

#define HIT          35
#define PEN          30

void
create_waterdeep_weapon()
{
    set_name(({ "mace", "club" }));
    set_adj(({ "flanged", "steel" }));

    set_short("flanged steel mace");
    set_long(
        CAP(LANG_ADDART(short())) + ". It is a wooden, leather-wrapped rod "
        + "with a steel mace head attached to one end. Flanges are affixed "
        + "along the head to increase its ability to penetrate armour. It "
        + "looks masterfully crafted.\n"
    );

    set_default_weapon(HIT, PEN, W_CLUB, W_BLUDGEON | W_SLASH, W_ANYH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_CLUB));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);

    add_prop(
        OBJ_S_WIZINFO,
        "This weapon is used by soldiers of the City Guard of Waterdeep.\n"
    );

    add_item(
        ({ "head", "mace head", "flange", "flanges" }),
        "The mace head is heavy and made of steel, with eight flanges affixed "
        + "along it.\n"
    );

    add_item(
        ({
            "rod", "wooden rod", "leather-wrapped rod", "handle", "shaft",
            "wrappings", "leather wrappings", "grip"
        }),
        "A hard, wooden rod makes up the shaft of the " + short() + ". Leather "
        + "wrappings increase the comfort and friction of the grip.\n"
    );
}
