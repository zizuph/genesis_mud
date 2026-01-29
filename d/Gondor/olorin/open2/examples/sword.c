inherit "/std/weapon";

#include <formulas.h>		// F_VALUE_WEAPON etc.
#include <stdproperties.h>	// OBJ_I_VALUE etc.
#include <wa_types.h>		// W_SWORD, W_IMPALE, etc.

#include "examples.h"

void
create_weapon()
{
    set_name("sword");
    add_name("shortsword");
    set_adj(({"short", "sharp", "double-edged", "steel"}));
    set_short("short steel sword");
    set_long("A short sword forged from steel. The double-edge blade "
      + "is very sharp.\n");

    // values set according to man weapon_guide:
    set_default_weapon(21, 16, W_SWORD, W_IMPALE, W_ANYH);

    // randomize the value, value below F_VALUE_WEAPON are impossible
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(21, 16) + random(51));

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(16, W_SWORD)
        + 200 - random(401));
    // the sword is mainly steel with a density of 8 g/cm^3
    // to take the hilt into account, reduce that density a little
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 6);
}

