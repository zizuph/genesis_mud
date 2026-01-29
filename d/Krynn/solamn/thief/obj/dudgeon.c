/* created by Aridor, 03/15/94 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("dudgeon");
    set_adj("ancient");
    add_name("dagger");
    set_short("ancient dudgeon");
    add_name("weapon");
    set_long("This is an ancient looking dagger type weapon with ornaments, " +
	     "but somehow it feels good in your hand, and sharp. Don't hurt " +
	     "yourself!\n");
    set_keep(1);
    set_default_weapon(13, 18, W_KNIFE, W_SLASH | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 60);
    add_prop(OBJ_I_WEIGHT, 600);
}

