// path:         /d/Krynn/solamn/hctower/spur/obj/pudding.c         
// creator(s):   Grace  28 Sep 94
// last update:  
// desc:         rice pudding
// note:         food for the mess hall in the Knights' Spur
// bug(s):
// to-do:        

inherit "/std/food";
#include "/sys/stdproperties.h"

        create_food()
        {
            set_amount(75);
            set_name("pudding");
            add_adj("rice");
            set_short("rice pudding");
            set_pshort("rice puddings");
            add_name("food");
            set_long("This is a small serving of rice pudding. It is "+
                "made from medium-grain rice boiled in a mixture of "+
                "cream, milk, sugar, vanilla, and cinnamon. It smells "+
                "delicious and should be easy on the stomach.\n");
        }

