/* created by Splunge 01/14/94 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("rapier");
    set_adj("steel");
    set_short("steel rapier");
    set_long("This thin sword is very sharp, but only on one side. " +
        "It's made of steel and looks like it would be very " +
        "effective for the removal of body parts.\n");
    set_default_weapon(31, 18 , W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 3600);
    add_prop(OBJ_I_WEIGHT, 1000);
}

