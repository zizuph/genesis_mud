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
    set_name("guards");
    set_ac(31);
    set_at(A_LEGS);
    set_am( ({ 5, -3, -2 }) );
    add_adj("blue");
    add_adj("shin");
    set_short("pair of blue shin guards");
    set_pshort("pairs of blue shin guards");
    set_long("A pair of blue shin guards, they are made of some bluish " +
	     "colored metal, which looks like a kind of steel.\n");
    add_prop(OBJ_I_VOLUME, 650);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(31, A_LEGS));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(31));
    add_prop(OBJ_I_COLORABLE, 1);
}


set_color(string new_color)
{
    remove_adj(color);
    color = new_color;
    set_adj(color);
    set_short("pair of " + color + " shin guards");
    set_pshort("pairs of " + color + " shin guards");
    set_long("A pair of shin guards, they are made of some " + color +
	     " colored metal, which looks like a kind of steel.\n");
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
    init_arm_recover(a[0]);
    set_color(a[1]);
}

