/* A dagger  */

inherit "/std/weapon";
inherit "/lib/keep";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

create_weapon()
{
    set_name("dagger"); set_pname("daggers");
    set_pname("daggers");
    set_short("dagger"); set_pshort("daggers");
    set_adj("sharp");
    add_adj("steel");
    set_long(break_string("This is a sharp steel dagger with " +
        "a broad blade and a wooden hilt covered with leather. " +
        "The backside of the blade is jagged so that the dagger " +
        "will tear large wounds in combat. \n",78));

    set_default_weapon(14,16,W_KNIFE,W_SLASH|W_IMPALE,W_ANYH,0);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(14,16)+random(80)-20);
    add_prop(OBJ_I_WEIGHT, 3200);
}
