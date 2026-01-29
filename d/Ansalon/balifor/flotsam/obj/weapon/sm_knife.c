inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("knife");
    set_adj("small");
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_short("small knife");
    set_long("A small knife, probably stolen from a kitchen. \n");
    set_default_weapon(12,13,W_SLASH | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 360);
    add_prop(OBJ_I_WEIGHT, 350);
}
