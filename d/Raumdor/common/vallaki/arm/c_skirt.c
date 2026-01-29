inherit "/std/armour";
#include "/d/Raumdor/defs.h"

string
random_color()
{
    switch(random(2))
    {
    case 0:
    return "black";
    break;
    case 1:
    return "white";
    break;
    }
}

void
create_armour()
{
    string color;
    color = random_color();
    ::create_armour();
    set_name("skirt");
    set_adj(color);
    set_short(color+" skirt");
    set_long("This is a nice, "+color+" cotton skirt.\n");
    set_at(A_LEGS);
    set_ac(1);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(OBJ_I_WEIGHT,600);
    add_prop(OBJ_I_VALUE,50);
}

