inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("halberd");
    set_adj("shiny");
    add_adj("steel");
    set_short("shiny steel halberd");
    set_long("This long steel weapon is of impressive make. A hardwood pole with an " +
      "axe-like blade made of precious steel firmly attached to the end of it, you do not " +
      "doubt this would make a fine weapon in anyones hands.\n");
    set_default_weapon(22,38, W_POLEARM, W_SLASH|W_IMPALE, W_BOTH);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 10000);
}
