// path:         /d/Krynn/solamn/hctower/spur/obj/cake.c         
// creator(s):   Grace  28 Sep 94
// last update:  
// desc:         chocolate cake
// note:         food for the mess hall in the Knights' Spur
// bug(s):
// to-do:        

inherit "/std/food";
#include "/sys/stdproperties.h"

        create_food()
        {
            set_amount(130);
            set_name("cake");
            add_name("food");
            add_adj("chocolate");
            set_short("slice of chocolate cake");
            set_pshort("slices of chocolate cake");

            set_long("This is nice large slice of rich chocolate cake. "+
                "It smells and looks heavenly, especially with the dark "+
                "chocolate icing on top.\n");
        }



