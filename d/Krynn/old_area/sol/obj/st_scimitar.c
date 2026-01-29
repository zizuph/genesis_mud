/* By Splunge 1/16/93 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("scimitar");
    set_adj("steel");
    set_adj("polished");
    set_long("This steel scimitar is preferred by most of the higher " +
	     "ranked officers in Takhisis' armies. It is often seen " +
	     "wielded by her goblins and draconians.\n");
    set_default_weapon(25, 25, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 1600);
    add_prop(OBJ_I_WEIGHT, 1500);
}

