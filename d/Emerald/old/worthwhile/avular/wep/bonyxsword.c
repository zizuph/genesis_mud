/*
 * BONYXSWORD.c
 * Barbed Onyx Broadsword
 * Used by the Avular Guards.
 * - Alaron JAN 2000
 */

#include "../defs.h"
#include "/d/Emerald/sys/macros.h"
#include <formulas.h>
#include <stdproperties.h>

inherit "/std/weapon";

void
create_weapon()
{
    set_name("broadsword");
    set_adj("barbed");
    add_adj("onyx");

    add_name("sword");

    set_long("The broadsword is light and extremely well balanced. The " +
        "onyx blade appears to have been carved painstakingly with "+
        "incredible precision. Jutting outward from the hilt and from the "+
        "very tip of the blade are small, extremely sharp barbs. This looks "+
        "like an extremely deadly weapon.\n");

    set_default_weapon(30, 28, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);

    set_likely_break(15); /* onyx is brittle */
    set_likely_dull(3); /* very well-made, low chance of dulling */
    set_likely_corr(5); /* its stone, resists acid better than iron */

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40, 32) -300);

}
