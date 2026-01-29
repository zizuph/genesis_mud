/* Ashlar, 31 Jul 97 */

#pragma strict_types
inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("scimitar");
    add_name("sword");
    set_adj("steel");
    set_short("steel scimitar");
    set_long("The scimitar has a broad curved blade, with a sharp " +
	"edge. A crossguard adorned with fancy scrollwork separates " +
	"the blade from the hilt which is wrapped in leather.\n");
    set_default_weapon(30,21,W_SWORD,W_SLASH | W_IMPALE, W_ANYH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}
