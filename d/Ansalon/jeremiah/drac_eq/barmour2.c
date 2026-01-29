inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

string color = "blue";


void
create_armour()
{
    set_name("mail");
    add_name("splint");
    set_adj(({"blue","splint"}));
    set_long("It's a blue splint mail of good quality, with golden patterns set into it.\n");
    set_default_armour(21);
    set_am(({1,1,-2}));
    add_prop(OBJ_I_COLORABLE, 1);
}


set_color(string new_color)
{
    remove_adj(color);
    color = new_color;
    set_adj(color);
    set_long("It's a " + color + " splint mail of good quality, with golden patterns set into it.\n");
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
