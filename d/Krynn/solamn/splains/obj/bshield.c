inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

string color = "blue";

set_color(string new_color)
{
    color = new_color;
    set_long("It's a not very large shield but it would still protect you.\n" +
         "It has " + color + " platings set into it.\n");
}

void
create_armour()
{
    set_name("shield");
    set_ac(12);
    set_at(A_SHIELD);
    set_am( ({ 6, -2, -4 }) );
    add_adj("small");
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_short("small shield");
    set_long("It's not a very large shield but it will protect you.\n" +
         "It has blue platings set into it.\n");
    add_prop(OBJ_I_VOLUME, 550);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(12, A_SHIELD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(12));
    add_prop(OBJ_I_COLORABLE, 1);
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

