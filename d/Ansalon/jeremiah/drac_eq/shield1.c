inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

string color = "blue";

void
set_color(string new_color)
{
    color = new_color;
    set_long("This is a large round shield. The face of the "
      + "shield bears the elaborate image of a " + color + " dragon. "
      + "Notches along the edge and dents across the face of this "
      + "shield, indicate that this shield has been used in combat.\n");
}

void
create_armour()
{
    set_name("shield");
    set_ac(19);
    set_at(A_SHIELD);
    set_am( ({ 6, -2, -4 }) );
    add_adj(({"large", "round"}));
    set_color("blue");
    add_prop(OBJ_I_VOLUME, 2550);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(19, A_SHIELD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(19));
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

