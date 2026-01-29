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
    set_amount(350);
    set_name("cheese");
    add_name(({"round", "food"}));
    add_pname(({"food", "foods", "foodstuff", "cheeses"}));
    add_adj(({"hard", "round"}));   
    set_short("round of hard cheese");
    set_long("This is a round of hard white cheese. It is "+
        "a bit chalky and hasn't much flavour, but it is high"+
        "ly nutritious.\n");
    set_keep(1);
    add_prop(OBJ_I_VALUE, 210);
}

