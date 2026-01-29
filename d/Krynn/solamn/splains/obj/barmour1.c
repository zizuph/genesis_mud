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
    set_name("armour");
    add_name("plate");
    set_ac(37);
    set_at(A_BODY);
    add_adj( ({ "blue", "plated", "plate" }) );
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_short(color + " plate armour");
    set_long("It's a body armour plated with blue scales.\n");
    add_prop(OBJ_I_VOLUME, 3040);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(25, A_BODY));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25));
    add_prop(OBJ_I_COLORABLE, 1);
}

void
set_color(string new_color)
{
    remove_adj(color);
    color = new_color;
    set_adj(color);
    set_long("It's a body armour plated with " + color + " scales.\n");
    set_short(color + " plate armour");
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

