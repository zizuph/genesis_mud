// path:         /d/Krynn/solamn/hctower/spur/obj/compote.c         
// creator(s):   Grace  28 Sep 94
// last update:  
// desc:         berry compote
// note:         food for the mess hall in the Knights' Spur
// bug(s):
// to-do:        

inherit "/std/food";
#include "/sys/stdproperties.h"

        create_food()
        {
            set_amount(100);
            set_name("compote");
            add_adj(({"berry", "fruit"}));
            set_short("berry compote");
            set_pshort("berry compotes");
            add_name("food");
            set_long("This is a small dish of raspberries, strawberries, "+
                "and blueberries, garnished with a bit of orange peel. "+
                "Over them has been poured a small portion of thick, " +
                "sweetened cream.\n");
        }





