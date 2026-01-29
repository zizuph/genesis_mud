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
    set_name("robe");
    set_ac(3);
    set_at(A_ROBE);
    add_adj("small");
    set_short("small robe");
    set_long(BS("It's made of soft and thick material, but yet it's not " +
           "very heavy. It is black but has a blue tinge to it. " +
           "As you look closer you can see fine blue threads woven into it.",SL));
    add_prop(OBJ_I_VOLUME, 4750);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(3, A_ROBE));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3));
    add_prop(OBJ_I_COLORABLE, 1);
}


set_color(string new_color)
{
    color = new_color;
    if (color == "black")
      set_long("It's made of soft and thick material, but yet it's not " +
           "very heavy.\nIt is deep " + color + ".\n");
    else
      set_long(BS("It's made of soft and thick material, but yet it's not " +
           "very heavy. It is black but has a " + color + " tinge to it. " +
           "As you look closer you can see fine " + color + " threads woven into it.",SL));
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

