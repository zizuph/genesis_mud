#include "/d/Ansalon/common/defs.h"

inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(25);
    set_name("beer");
    set_adj("roke");
    set_short("imported roke beer");
    set_long("This is one of the famous roke beers from "+
             "the lost land of Re Albi. These beers are "+
             "notorious for their high level of alcohol.\n");
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 100);
    seteuid(getuid());
}


void
special_effect(int numofdrinks)
{
    object add;
    
    seteuid(getuid());
    add = clone_object("/d/Ansalon/goodlund/nethosak/"+
                       "city/obj/booze_object");
    add->move(TP,1);
        
}
