inherit "/std/object";
#include "/d/Raumdor/defs.h"
/* SARR */

string name;
string adj;

string
random_toy()
{
    switch(random(3))
    {
        case 0:
        adj = "wooden";
        return "soldier";
        break;
        case 1:
        adj = "stuffed";
        return "doll";
        break;
        case 2:
        adj = "wooden";
        return "horse";
        break;
    }
}


void
create_object()
{
    name = random_toy();
    set_name(name);
    set_adj(adj);
    set_short(adj+" "+name);
    set_long("@@my_long");
    add_prop(OBJ_I_WEIGHT,500);
    add_prop(OBJ_I_VOLUME,300);
    add_prop(OBJ_I_VALUE,20);
}

string
my_long()
{
    if(name == "soldier")
    {
        return 
        "This is a tiny toy soldier made of wood. It is very nicely "+   
        "carved, showing the detailed armour, shield and sword of "+   
        "the figure.\n";
    }
    if(name == "horse")
    {
        return
        "This is a tiny carving of a horse. You see the detailed "+
        "eyes, tail and legs. It looks very nice.\n";
    }
    if(name == "doll")
    {
        return
        "This is a little ragged doll. It has a diry shirt, and "+
        "tangled hair. Despite that, it has a big smile on her "+ 
        "face.\n";
    }
}

