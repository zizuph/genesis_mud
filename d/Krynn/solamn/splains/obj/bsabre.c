/* created by Aridor 07/13/93 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("sabre");
    set_adj("curved");
    set_short("curved sabre");
    set_long("A typical army weapon of above average quality.\n");
    set_default_weapon(26, 23, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 2600);
    add_prop(OBJ_I_WEIGHT, 2500);
}

