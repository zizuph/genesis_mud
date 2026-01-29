// path:         /d/Krynn/solamn/hctower/spur/obj/brie.c         
// creator(s):   Grace  28 Sep 94
// last update:  
// desc:         a wedge of brie cheese (french cheese)
// note:         food for the mess hall in the Knights' Spur
// bug(s):
// to-do:        

inherit "/std/food";
#include "/sys/stdproperties.h"

        create_food()
        {
            set_amount(200);
            set_name("brie");
            add_name(({"cheese", "wedge"}));
            add_name("food");
            add_adj(({"hard","ripe","yellow-orange", "mild"}));
            set_short("wedge of soft cheese");
            set_pshort("wedges of soft cheese");
            set_long("This is a wedge of soft, ripened cheese. It has "+
                "a pungent flavour, a creamy texture, and an edible "+
                "chalky crust.\n");
        set_heap_size(1);
            add_item("crust","It is chalky-white, and looks a bit "+
                "unappetizing.\n");
        }
