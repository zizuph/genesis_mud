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
    set_amount(200);
    set_name("nuts");
    add_name("packet");
    add_pname(({"food", "foods", "foodstuff"}));
    add_adj(({"packet", "nuts"}));   
    set_short("packet of nuts");
    set_long("This packet contains a mixture of nuts, "+
       "which are high in protein and fat and thus very "+
       "good sources of energy.\n");
    set_keep(1);
    add_prop(OBJ_I_VALUE, 75);
}

