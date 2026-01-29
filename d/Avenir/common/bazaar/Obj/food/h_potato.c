// path:         /d/Avenir/common/bazaar/obj/h_potato.c
// creator(s):   Grace  28 Sep 94
// last update:  
// desc:         hash brown potatoes     
// note:         food for the Dancing Potatoe Inn.
// bug(s):
// to-do:       

inherit "/std/food";
#include "/sys/stdproperties.h"

        create_food()
        {
            set_amount(250);
            set_name("potato");
            add_name("plate");
            add_adj(({"hash", "brown", "hash brown"}));   
            set_short("plate of hash brown potatoes");
            set_long("A plate covered with grated potatoes fried in oil. "+
                "They are heavily salted and it smells like the oil is "+
                "slightly rancid. They are so unappetizing that only a "+
                "truly hungry person would eat them.\n");
            add_item(({"substance", "oil"}), 
                "You won't believe it's not butter.\n");
        }
