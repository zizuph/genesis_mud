inherit "/std/object";
#include "/d/Raumdor/defs.h"

string
random_metal()
{
    switch(random(4))
    {
       case 0:
       return "steel";
       break;
       case 1:
       return "silver";
       break;
       case 2:
       return "gold";
       break;
       case 3:
        return "steel";
       break;
    }
}


void
create_object()
{
    int val;
    string metal = random_metal();
    set_name("cross");
    set_adj(metal);
    set_short(metal+" cross");
    set_long("This a beautifully crafted cross made of pure "+metal+
    ". On the edge you see written: The holy power is within.\n");
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,80);
    if(metal = "steel")
        val = 100;
    if(metal = "silver")
        val = 150;
    if(metal = "gold")
        val = 250;
    add_prop(OBJ_I_VALUE,val);
}

