// path:         /d/Krynn/solamn/hctower/spur/obj/s_pasta.c         
// creator(s):   Grace  28 Sep 94
// last update:  
// desc:         a small dish of pasta      
// note:         food for the mess hall in the Knights' Spur
// bug(s):
// to-do:        

inherit "/std/food";
#include "/sys/stdproperties.h"

        create_food()
        {
            set_amount(120);
            set_name("pasta");
            add_name(({"noodles", "dish"}));
            add_adj("small");
            set_short("small dish of pasta");
            set_pshort("small dishes of pasta");
            add_name("food");
            set_long("This is a small dish of pasta. The thin noodles have "+
                "been lightly buttered and salted.\n");
            add_item("noodles", "The noodles are thin and made from flour "+
                "and egg.\n"); 
        }

