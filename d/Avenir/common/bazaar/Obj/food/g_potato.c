// path:         /d/Avenir/common/bazaar/obj/g_potato.c
// creator(s):   Grace  28 Sep 94
// last update:  
// desc:         au gratin potato      
// note:         food for the Dancing Potatoe Inn.
// bug(s):
// to-do:       

inherit "/std/food";
#include "/sys/stdproperties.h"

        create_food()
        {
            set_amount(300);
            set_name("potato");
            add_name("crock");
            add_adj("au gratin");   
            set_short("crock of au gratin potatoes");
            set_long("Your mother used to make a dish with the same name, "+
                "but there the resemblence ends. A cracked pottery bowl is "+
                "filled with round slices of potato congealing in a clotted "+
                "yellow-orange sauce.\n");
            add_item("sauce", "It looks like it is trying (and failing) "+
                "to resemble a cheese sauce.\n");
        }
