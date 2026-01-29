/* created by Aridor 12/96 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

void
create_weapon()
{
    set_name("sword");
    add_name("shortsword");
    set_adj("short");
    set_short("short sword");
    set_long("It's a standard short sword.\n");
    set_default_weapon(15, 10, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 900);
    add_prop(OBJ_I_WEIGHT, 900);
}
