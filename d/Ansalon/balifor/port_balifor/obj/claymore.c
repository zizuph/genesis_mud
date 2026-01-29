/* added keepability - Torqual 15.01.2001 */
inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("sword");
    add_name("claymore");
    set_adj("dragon");
    add_adj("marked");
    add_adj("dragon-marked");
    set_short("dragon-marked claymore");
    set_long("This great two-handed sword of steel is of fine make, well " +
      "balanced, with a hilt resembling a great dragon in flight.  It would " +
      "be deadly in the hands of a swordsmaster.\n");
    set_default_weapon(40, 32, W_SWORD, W_SLASH, W_BOTH);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 10000);
}
