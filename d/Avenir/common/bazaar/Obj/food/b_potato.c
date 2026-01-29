// path:         /d/Avenir/common/bazaar/obj/b_potato.c
// creator(s):   Grace  28 Sep 94
// last update:  
// desc:         baked potato      
// note:         food for the Dancing Potatoe Inn.
// bug(s):
// to-do:       

inherit "/std/food";
#include "/sys/stdproperties.h"

        create_food()
        {
            set_amount(130);
            set_name("potato");
            add_adj("baked");   
            set_short("large baked potato");
            set_long("The top of this potato has been squeezed open. "+
                "Black specks which look like pepper swim in an oily, "+
                "yellow substance which is probably, hopefully, butter.\n");
            add_item("specks", "Looking at the specks, you are trying to "+
                "convince yourself that they are simply ground pepper.\n"); 
            add_item(({"substance", "oil"}), 
                "You won't believe it's not butter.\n");
        }
