inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

string
random_color()
{
    int i = random(6);
    switch(i)
    {
        case 0:
        return "blue";
        break;
        case 1:
        return "white";
        break;
        case 2:
        return "green";
        break;
        case 3:
        return "red";
        break;
        case 4:
        return "black";
        break;
        default:
        return "yellow";
        }
}

void
create_armour()
{
    ::create_armour();
    set_name("tunic");
    set_adj("silk");
    add_adj(random_color());
    set_short(random_color()+" silk tunic");
    set_long("This is a plain silk tunic that looks very expensive. "+
    "Only rich citizens could afford such valuable clothes.\n");
    set_ac(1);
    set_at(A_TORSO);
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,80);
    add_prop(OBJ_I_VALUE,200);
}

