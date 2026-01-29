/* Ashlar, 9 Jun 97 - broadsword for the city guards */
/* original by Carridin */

#pragma strict_types
inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name(({"sword", "broadsword"}));
    set_adj("polished");
    set_short("polished broadsword");
    set_long("The blade of this average-sized broadsword has been well " +
	    "cared for. Not a single scratch can be found along the shiny " +
	    "steel, and the cutting edges has been sharpened with care.\n");
    set_default_weapon(30, 27, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}
