inherit "/std/armour";
#include "/d/Raumdor/defs.h"

string
random_metal()
{
    switch(random(4))
    {
       case 0:
       return "silver";
       break;
       case 1:
       return "gold";
       break;
       case 2:
       return "platinum";
       break;
       case 3:
       return "silver";
       break;
    }
}


void
create_armour()
{
    int val;
    string metal = random_metal();
    ::create_armour();
    set_name("necklace");
    set_adj(metal);
    set_short(metal+" necklace");
    set_long("This a beautiful "+metal+" necklace. It sparkles in the "+
    "light.\n");
    set_at(A_NECK);
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,80);
    if(metal == "silver")
        val = 100;
    if(metal == "gold")
        val = 200;
    if(metal == "platinum")
        val = 250;
    add_prop(OBJ_I_VALUE,val);
}

