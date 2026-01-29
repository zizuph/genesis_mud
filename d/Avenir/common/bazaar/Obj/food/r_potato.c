
// path:         /d/Avenir/common/bazaar/obj/r_potato.c
// creator(s):   Grace  28 Sep 94
// last update:  
// desc:         fried potato rounds     
// note:         food for the Dancing Potatoe Inn.
// bug(s):
// to-do:       

inherit "/std/food";
#include "/sys/stdproperties.h"

        create_food()
        {
            set_amount(450);
            set_name("potato");
            add_name("basket");
            add_adj(({"round", "rounds", "fried"}));   
            set_short("basket of fried potato rounds");
            set_long("This is a basket filled to capacity with fried  "+
                "round slices of potatoes. The paper lining is soaked "+
                "with oil, and the potatoes, though perhaps at one time "+
                "crispy, are now limp. It looks edible, but not very "+
                "appetizing.\n");
            add_item("basket", "It is somehow made of bread.\n"); 
            add_item(({"substance", "oil"}), 
                "You won't believe it's not butter.\n");
        }

