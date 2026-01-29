// path:         /d/Krynn/solamn/hctower/spur/obj/d_fruit.c         
// creator(s):   Grace  28 Sep 94
// last update:  
// desc:         dried fruit mix
// note:         food for the mess hall in the Knights' Spur
// bug(s):
// to-do:        

inherit "/std/food";
#include "/sys/stdproperties.h"

        create_food()
        {
            set_amount(300);
            set_name("fruit");
            add_name(({"mix", "package"}));
            add_adj("dried");
            set_short("package of dried fruit");
            set_pshort("packages of dried fruit");
            add_name("food");
            set_long("This is a mixture of dried fruits, preserved so "+
                "people may eat well despite fruit being out-of-season. "+
                "You can make out bits of dried apples, bananas, apricots, "+
                "plums, and orange peel, as well as some nuts.\n");
        }

