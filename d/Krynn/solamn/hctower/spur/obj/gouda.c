// path:         /d/Krynn/solamn/hctower/spur/obj/gouda.c         
// creator(s):   Grace  28 Sep 94
// last update:  
// desc:         a ball of gouda cheese (dutch cheese)
// note:         food for the mess hall in the Knights' Spur
// bug(s):
// to-do:        

inherit "/std/food";
#include "/sys/stdproperties.h"

        create_food()
        {
            set_amount(125);
            set_name("gouda");
            add_name(({"cheese", "ball"}));
            add_adj(({"hard","ripe","yellow-orange", "mild"}));
            set_short("ball of mild orange cheese");
            set_pshort("balls of mild orange cheese");
            add_name("food");
            set_long("This is a flattened ball of yellow-orange cheese. It is "+
                "hard and ripened, with a mild flavour.\n");
        }
