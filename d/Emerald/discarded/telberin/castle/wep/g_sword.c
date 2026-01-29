inherit "/std/weapon";

#include "default.h"

void
create_weapon()
{
    set_name("sword");
    set_short("guard sword");
    set_long("This sword is a fairly well made sword, but nothing special " +
             "to say the least.\n");
    set_adj("guard");

    set_default_weapon(21, 24, W_SWORD, W_SLASH | W_IMPALE, W_ANYH,  0);
    add_prop(OBJ_I_WEIGHT, 2080); 
    add_prop(OBJ_I_VOLUME,  860); 
    add_prop(OBJ_I_VALUE, 700);
}
