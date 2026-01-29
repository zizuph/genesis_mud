// path:         /d/Krynn/solamn/hctower/spur/obj/stew.c         
// creator(s):   Grace  28 Sep 94
// last update:  
// desc:         a vegetable stew      
// note:         food for the mess hall in the Knights' Spur
// bug(s):
// to-do:        add the props from the mentioned herbs to this food ?

inherit "/std/food";
#include "/sys/stdproperties.h"

        create_food()
        {
            set_amount(1000);
            set_name("stew");
            add_name("vegetable stew");
            add_adj("vegetable");   
            set_short("crock of vegetable stew");
            set_pshort("crocks of vegetable stew");
            add_name("food");
            set_long("This crock is filled with a thick and aromatic stew. "+
                "Very nourishing to the body, this stew is made with beans, "+
                "potatoes, cabbage, tomatoes, squash, peppers, carrots, "+
                "celery and onions, as well as numerous undistinguishable "+
                "herbs. A thin layer of cheese has been grated onto the surface.\n");
            add_item("crock", "It is a simple pottery crock, used to keep "+
                "soups and stews warm.\n"); 
        }
