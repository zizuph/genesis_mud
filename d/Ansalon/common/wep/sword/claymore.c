#pragma strict_types
inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("sword");
    add_name("claymore");
    set_adj("golden");
    add_adj("golden-hued");
    add_adj("steel");
    set_short("golden-hued claymore");
    set_long("This great two-handed sword of steel is of fine make, well balanced, " +
      "with the blade dyed a golden hue. It would be deadly " +
      "in the hands of a swordsmaster.\n");
    set_default_weapon(39, 33, W_SWORD, W_SLASH, W_BOTH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}
