/* created by Aridor 07/13/93 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("lance");
    set_adj("footman");
    set_short("footman lance");
    set_long("This is a rather primitive weapon, but has a pointy tip.\n");
    set_default_weapon(13, 13, W_POLEARM, W_IMPALE, W_BOTH);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_WEIGHT, 800);
}

