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
    set_name("mask");
    set_ac(35);
    set_at(A_HEAD);
    set_am( ({ -4, 4, 0 }) );
    add_adj( ({ "dark night-blue", "face" }) );
    set_long("It's a dark night-blue face mask. You are not able to hide " +
             "your face when you wear it, but you can are positive this " +
             "is an excellent piece of armour. Not only your face, but " +
             "your entire head is protected with it.\n");
    add_prop(OBJ_I_VOLUME, 550);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(35, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(35));
    add_prop(OBJ_I_COLORABLE, 1);
}


set_color(string new_color)
{
    remove_adj(color);
    color = new_color;
    set_adj(color);
    set_long("It's a " + color + " face mask. You are not able to hide " +
             "your face when you wear it, but you can are positive this is " +
             "an excellent piece of armour. Not only your face, but your " +
             "entire head is protected with it.\n");
    set_short(0);
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

