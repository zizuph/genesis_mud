/* created by Aridor 07/13/93 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("dagger");
    set_adj("sharp");
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_short("sharp dagger");
    set_long("This is a sharp weapon, don't hurt yourself!\n");
    set_default_weapon(19, 11, W_KNIFE, W_SLASH | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_WEIGHT, 800);
}

