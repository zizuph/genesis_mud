#pragma strict_types
#pragma save_binary

inherit "/std/armour";

#include <formulas.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("crown");
    set_adj("gold");
    set_short("gold crown");
    set_long("The crown is made of gold and covered with diamonds.\n");
    set_ac(24);
    set_at(A_HEAD);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 5000);

    add_prop(OBJ_I_VALUE,25000);
}

