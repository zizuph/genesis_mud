// path:         /d/Krynn/solamn/hctower/spur/obj/capon.c         
// creator(s):   Grace  28 Sep 94
// last update:  
// desc:         a roasted capon      
// note:         food for the mess hall in the Knights' Spur
// bug(s):
// to-do:        add the props from the mentioned herbs to this food ?

inherit "/std/food";
#include "/sys/stdproperties.h"

        create_food()
        {
            set_amount(1000);
            set_name("capon");
            add_name(({"cock", "roast"}));
            add_adj("large");   
            set_short("roasted capon with aspic");
            set_pshort("roasted capons with aspic");
            add_name("food");
            set_long("This is one-half of a large roasted capon. The skin is "+
                "golden-brown and sprinkled with herbs. The aspic is cut into "+
                "cubes and made from the capon-broth and a touch of dry sherry. "+
                "The smell is so delicious that your mouth waters.\n");
            add_item("aspic", "A garnish made from gelatin, sherry and broth, "+
                "it is a tasty accompaniment to the capon roast.\n"); 
        }
