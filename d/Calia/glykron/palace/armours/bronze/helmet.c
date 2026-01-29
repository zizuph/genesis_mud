/* 	bronze helmet for the bronze knight in the crystalline palace

    coder(s):   Glykron

    history:     9. 2.92    header added                    Glykron
                 9. 2.92    last modified                   Glykron

*/

#pragma save_binary

inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("helmet");
    set_adj("bronze");
    set_short("bronze helmet");
    set_long("This is a pointy helmet made of bronze.\n");
    set_ac(15);
    set_at(A_HEAD);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 3000);
}