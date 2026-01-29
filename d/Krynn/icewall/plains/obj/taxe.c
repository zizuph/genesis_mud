/*Created by Macker 09/23/94 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>



create_weapon()
{
    set_name("battleaxe");
    add_name("axe");
    set_short("sharp steel battleaxe");
    set_adj("steel");
    set_adj("sharp");
    set_long("This is a nice looking, sharp battleaxe. " +
	     "Although there is nothing extremely unique " +
	     "about this weapon it appears to be of good " +
	     "make.\n");
    set_default_weapon(32, 34, W_AXE, W_SLASH, W_BOTH);
    add_prop(OBJ_I_VOLUME, 2200);
    add_prop(OBJ_I_WEIGHT, 2200);
}
