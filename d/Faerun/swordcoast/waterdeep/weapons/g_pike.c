/*
 * waterdeep/weapons/g_pike.c
 * A pike used by soldiers in the City Guard
 *
 * Created by Brine, Feb 2021
 */

#pragma strict_types

#include "../defs.h"

inherit WATERDEEP_WEP;

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

#define HIT          40
#define PEN          35

void
create_waterdeep_weapon()
{
    set_name(({ "pike", "spear", "polearm" }));
    set_adj(({ "long", "steel-headed" }));

    set_short("long steel-headed pike");
    set_long(
        CAP(LANG_ADDART(short())) + ". It is a wooden shaft of approximately "
        + "15 feet length, with a steel spearhead affixed. Its length and "
        + "weight makes it necessary to use both hands to wield it. It looks "
        + "masterfully crafted.\n"
    );

    set_default_weapon(HIT, PEN, W_POLEARM, W_IMPALE | W_SLASH, W_BOTH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_POLEARM));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);

    add_prop(
        OBJ_S_WIZINFO,
        "This weapon is used by soldiers of the City Guard of Waterdeep.\n"
    );

    add_item(
        ({ "shaft", "wooden shaft", "wood", "ash wood" }),
        "The shaft is made of well-seasoned ash wood, giving it great strength "
        + "and stability.\n"
    );

    add_item(
        ({
            "head", "spearhead"
        }),
        "A steel spearhead with razor-sharp edges and point is affixed at the "
        + "end of the " + short() + ".\n"
    );

    add_item(
        ({ "edge", "edges", "point" }),
        "The edges and the point are razor-sharp and undoubtedly lethal.\n"
    );
}
