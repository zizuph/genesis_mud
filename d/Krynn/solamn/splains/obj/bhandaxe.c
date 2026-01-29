/* created by Aridor 07/13/93 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("handaxe");
    set_adj("primitive");
    set_short("primitive handaxe");
    set_long("This is a rather primitive weapon, but looks very sharp.\n");
    set_default_weapon(9, 13, W_AXE, W_SLASH | W_BLUDGEON, W_RIGHT);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_WEIGHT, 800);
}

