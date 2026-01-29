// path:         /d/Avenir/common/bazaar/obj/p_potato.c
// creator(s):   Grace  28 Sep 94
// last update:  
// desc:         potato pancackes      
// note:         food for the Dancing Potatoe Inn.
// bug(s):
// to-do:       

inherit "/std/food";
#include "/sys/stdproperties.h"

        create_food()
        {
            set_amount(150);
            set_name("potato");
            add_name("pancakes");
            add_adj("fired");   
            set_short("plate of potato pancakes");
            set_long("This is the specialty of the house. Made of shredded "+
                "potato and onion mixed with eggs and fried until golden-"+
                "brown, these pancakes actually look quite tasty!\n");
        }

