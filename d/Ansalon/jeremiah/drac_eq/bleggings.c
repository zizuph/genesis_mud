inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

string color = "blue";


void
create_armour()
{
    set_name("leggings");
    set_ac(20);
    set_at(A_LEGS);
    set_am( ({ 5, -3, -2 }) );
    add_adj("blue");
    set_short("pair of blue leggings");
    set_pshort("pairs of blue leggings");
    set_long("A pair of blue leggings, they are made of iron.\n");
    add_prop(OBJ_I_VOLUME, 450);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_LEGS));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20));
    add_prop(OBJ_I_COLORABLE, 1);
}


set_color(string new_color)
{
    remove_adj(color);
    color = new_color;
    add_adj(color);
    set_short("pair of " + color + " leggings");
    set_pshort("pairs of " + color + " leggings");
    set_long("A pair of " + color + " leggings, they are made of iron.\n");
}




string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + color;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    set_color(a[1]);
    init_arm_recover(a[0]);
}

