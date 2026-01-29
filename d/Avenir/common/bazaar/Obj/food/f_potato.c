// path:         /d/Avenir/common/bazaar/obj/f_potato.c
// creator(s):   Grace  28 Sep 94
// last update:  
// desc:         french fries     
// note:         food for the Dancing Potatoe Inn.
// bug(s):
// to-do:       

inherit "/std/food";
#include "/sys/stdproperties.h"

        create_food()
        {
            set_amount(75);
            set_name("potato");
            add_name(({"french fries", "fries"}));
            add_adj(({"french", "fried"}));   
            set_short("packet of french fries");
            set_long("Long, thin rectangular slices of potato fried in oil. "+
                "These are the saddest looking fries you've ever seen. They "+
                "look wilted and mushy. You aren't sure what kind of oil "+
                "they were fried in, but it has given them a glistening "+
                "grayish tinge reminiscent of the brains of your fallen "+
                "enemies.\n");
            add_item(({"substance", "oil"}), 
                "You wont believe it's not butter.\n");
        }
