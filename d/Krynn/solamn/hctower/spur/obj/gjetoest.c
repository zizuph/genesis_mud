// path:         /d/Krynn/solamn/hctower/spur/obj/gjetoest.c         
// creator(s):   Grace  28 Sep 94
// last update:  
// desc:         a cube of gjetoest cheese (good norwegian cheese)
// note:         food for the mess hall in the Knights' Spur
// bug(s):
// to-do:        

inherit "/std/food";
#include "/sys/stdproperties.h"

        create_food()
        {
             set_amount(28);
            set_name("gjetoest");
            add_name(({"cheese", "cube"}));
            add_adj(({"firm","unripe","golden-brown", "whey", "sweet"}));
            set_short("cube of whey cheese");
            set_pshort("cubes of whey cheese");
            add_name("food");
            set_long("This is a small cube of golden-brown cheese. It is "+
                "a type of whey cheese, firm and unripened, with a sweet " +
                "taste.\n");
        }

