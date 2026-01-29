inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

int value;

string
set_gem()
{
    int i;
    i = random(6);
    switch(i)
    {
        case 0:
        value = 200;
        return "sapphire";
        break;
        case 1:
        value = 250;
        return "jade";
        break;
        case 2:
        value = 300;
        return "opal";
        break;
        case 3:
        value = 400;
        return "emerald";
        break;
        case 4:
        value = 500;
        return "ruby";
        break;
        case 5:
        value = 600;
        return "diamond";
        break;
    }
}


void
create_armour()
{
    string gem = set_gem();
    ::create_armour();
    set_name("ring");
    set_adj(gem);
    set_short(gem+" ring");
    set_long("This is a very beautiful and finely crafted ring "+
        "made of solid gold. In the center of it, is a very nice "+
        "looking "+gem+" gem.\n");
    set_ac(0);
    set_at(A_ANY_FINGER);
    add_prop(OBJ_I_WEIGHT,40);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE,value);
}

