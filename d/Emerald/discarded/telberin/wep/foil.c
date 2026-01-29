inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
void
create_weapon()
{
    set_name("foil");
    set_short("elven foil");
    set_long("This delicate elven weapon is used by experts or fools. It is " +
             "thin and looks like it is pretty sound.\n");
    set_adj("elven");

    set_default_weapon(15, 21, W_SWORD, W_SLASH | W_IMPALE, W_ANYH,  0);
    add_prop(OBJ_I_WEIGHT, 1890); 
    add_prop(OBJ_I_VOLUME,  1100);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(15, 21) + random(20));
}
 
