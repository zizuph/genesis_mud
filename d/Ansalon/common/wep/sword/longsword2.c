/* Ashlar, 21 Aug 97 */

#pragma strict_types
inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("longsword");
    add_name("sword");
    set_adj("heavy");
    add_adj("iron");
    set_short("heavy longsword");
    set_long("The heavy longsword is made of iron and appears quite " +
	"old. It has not been well cared for, which is apparent " +
	"from the nicks in the blade.\n");
    set_default_weapon(28,26,W_SWORD,W_SLASH | W_IMPALE, W_ANYH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}
