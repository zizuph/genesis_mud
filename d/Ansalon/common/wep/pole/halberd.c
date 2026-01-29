inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("halberd");
    set_adj("shiny");
    add_adj("steel");
    set_short("shiny steel halberd");
    set_long("This long steel weapon is of impressive make. A hardwood pole with an " +
      "axe-like blade made of precious steel firmly attached to the end of it, you do not " +
      "doubt this would make a fine weapon in anyones hands.\n");
    set_default_weapon(22,38, W_POLEARM, W_IMPALE | W_SLASH, W_BOTH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/7);
}
