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
    set_amount(450);
    set_name("hard sausage");
    add_name("sausage");
    add_pname(({"food", "foods", "foodstuff", "sausages"}));
    add_adj(({"hard", "spicy"}));   
    set_short("hard sausage");
    set_long("This is a spicy, garlic-flavoured sausage. "+
        "The meat has been salted and preserved so that it "+
        "will not spoil.\n");
    set_keep(1);
    add_prop(OBJ_I_VALUE, 350);
}


