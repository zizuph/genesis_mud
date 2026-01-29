/*
 * waterdeep/armour/g_cuirass.c
 * Cuirass worn by soldiers of the City Guard of Waterdeep
 *
 * Created by Brine, Feb 2021
 */

#pragma strict_types

#include "../defs.h"

inherit WATERDEEP_ARM;

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

#define AC          35
#define A_MOD       ({ -2, 1, 1 })
#define TYPE        A_TORSO

void
create_waterdeep_armour()
{
    set_name("cuirass");
    set_adj(({ "polished", "steel" }));

    set_short("polished steel cuirass");
    set_long(
        CAP(LANG_ADDART(short())) + ". It consists of two steel plates, a "
        + "breastplate and a back-plate, that are strapped together with "
        + "leather bands over a padded undercoat. It has been polished to a "
        + "shine, and looks masterfully crafted.\n"
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
        ({ "breastplate", "breast plate", "breast-plate" }),
        "A thin steel plate, shaped to fit over the chest. It is shaped "
        + "slightly like a wedge towards the center, to deflect the force of "
        + "blows and projectiles away from the torso of the wearer.\n"
    );

    add_item(
        ({ "backplate", "back-plate", "back plate" }),
        "A thin steel plate, shaped to fit over the back.\n"
    );

    add_item(
        ({ "bands", "leather bands" }),
        "Strong leather bands strap the breastplate and the back-plate "
        + "together firmly.\n"
    );

    add_item(
        ({ "undercoat", "padded undercoat" }),
        "An undercoat of padded cloth provides comfort and warmth to the "
        + "wearer, as well as some added protection.\n"
    );
}
