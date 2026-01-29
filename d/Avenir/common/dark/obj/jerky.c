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
    set_amount(150);
    set_name("jerky");
    add_name("strip");
    add_pname(({"food", "foods", "foodstuff"}));
    add_adj(({"hard", "spicy", "garlic"}));   
    set_short("jerky strip");
    set_pshort("jerky strips");
    set_long("This meat has been smoked at a low temperature "+
        "until it dried. It is smoke-flavored and salty, and "+
        "the consistency of shoe-leather. It does, however, "+
        "have some nutritional value.\n");
    set_keep(1);
    add_prop(OBJ_I_VALUE, 45);
}

