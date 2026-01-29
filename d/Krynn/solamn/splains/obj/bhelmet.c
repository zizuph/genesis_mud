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
    set_name("helmet");
    set_ac(9);
    set_at(A_HEAD);
    set_am( ({ -5, 0, 5 }) );
    add_adj( ({ "small", "blue" }) );
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_short("small helmet");
    set_long("It's a small blue helmet.\n");
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(9, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(9));
    add_prop(OBJ_I_COLORABLE, 1);
}


set_color(string new_color)
{
    remove_adj(color);
    color = new_color;
    add_adj(color);
    set_long("It's a small " + color + " helmet.\n");
    set_short("small " + color + " helmet");
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

