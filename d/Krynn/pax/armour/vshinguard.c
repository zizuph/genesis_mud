inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h";
#include "/d/Krynn/pax/local.h"

string color = "dark night-blue";


void
create_armour()
{
    set_name("guards");
    set_ac(31);
    set_at(A_LEGS);
    set_am( ({ 5, -3, -2 }) );
    add_adj(({ "shin", "dark", "night-blue" }));
    set_short("pair of dark night-blue shin guards");
    set_pshort("pairs of dark night-blue shin guards");
    set_long("A pair of dark night-blue chin guards, they are made of " +
             "some dark bluish colored metal, which looks like a kind " +
             "of steel.\n");
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
    color = a[1];
    init_arm_recover(a[0]);
}

