inherit "/std/armour";
#include "/d/Raumdor/defs.h"

string
random_color()
{
    switch(random(5))
    {
    case 0:
    return "blue";
    break;
    case 1:
    return "red";
    break;
    case 2:
    return "yellow";
    break;
    case 3:
    return "black";
    break;
    case 4:
    return "green";
    break;
    }
}

void
create_armour()
{
    string color;
    color = random_color();
    ::create_armour();
    set_name("tunic");
    set_adj(color);
    set_short(color+" tunic");
    set_long("This is a nice, "+color+" cotton tunic.\n");
    set_at(A_TORSO);
    set_ac(1);
    add_prop(OBJ_I_VALUE,80);
    add_prop(OBJ_I_WEIGHT,600);
    add_prop(OBJ_I_VOLUME,500);
}

