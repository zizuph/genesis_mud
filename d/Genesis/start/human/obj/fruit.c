// path:         
// creator(s):   
// desc:         
// note:         
// last update:  
// bug(s):
// to-do:       

inherit "/std/food";
inherit "/lib/keep";

#include "/sys/stdproperties.h"

void
create_food()
{
    set_amount(50);
    set_name("dried fruit");
    add_name("fruit");
    add_pname(({"food", "foods", "foodstuff","fruits"}));
    add_adj(({"dried"}));   
    set_short("dried fruit");
    set_long("This is a bit of dried fruit. The exterior "+
        "is dry and wrinkled, but the meaty interior is "+
        "succulent and flavourful.\n");
    set_keep(1);
    add_prop(OBJ_I_VALUE, 10);
}

