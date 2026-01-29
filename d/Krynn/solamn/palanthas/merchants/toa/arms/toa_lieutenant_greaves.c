/*
 * Greaves worn by the Lieutenant of the Constabulary of Palanthas found
 * in the Tower of Arms.
 *
 * Mortis 9.2014
 *
 */
inherit "/std/armour";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include "../../../local.h"

#define VK_NOBUY "_vkeep_shop_no_buy"
#define GREAVES_AC 45

public void
create_armour()
{
    set_name("greaves");
    set_adj("strapped");
    add_adj(({"plate"}));
    set_short("pair of strapped plate greaves");
    set_pshort("pairs of strapped plate greaves");
    set_long("These greaves cover the legs from hip to ankle in fine steel "
        + "chain mesh. The outer thighs are masterfully angled platemail with "
        + "a series of grey leather straps buckling them snugly inside the "
        + "thigh. The shin guard plates rise up to shield the knees and are "
        + "also strapped snugly into place leaving no unguarded openings "
        + "anywhere across the legs.\n");

    set_ac(GREAVES_AC);
    set_am(({1, 0, -1}));
    set_at(A_LEGS);

    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VALUE, 2200);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO, ({"This armour is enchanted.\n", 5, "The "
        + "greaves themselves were crafted by an armour master, but the "
        + "steel in the chain mesh itself is imbued with abjuration "
        + "magic which should deflect blows to some degree.\n", 25}));
    add_prop(MAGIC_AM_MAGIC,({55, "abjuration"}));
    add_prop(OBJ_S_WIZINFO,"These are enchanted for strong protection, "
        + "nothing more. The quality is fantastic plus the chainmail is "
        + "abjuration enchanted. That's about it.\n");
    add_prop(VK_NOBUY, 1);
}
