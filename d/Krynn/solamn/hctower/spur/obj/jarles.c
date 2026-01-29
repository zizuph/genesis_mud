// path:         /d/Krynn/solamn/hctower/spur/obj/jarles.c         
// creator(s):   Grace  28 Sep 94
// last update:  
// desc:         a slice of jarlesberg cheese (good norwegian cheese)
// note:         food for the mess hall in the Knights' Spur
// bug(s):
// to-do:        

inherit "/std/food";
#include "/sys/stdproperties.h"

        create_food()
        {
            set_amount(60);
            set_name("jarles");
            add_name(({"cheese", "slice"}));
            add_adj(({"firm","ripe","yellow", "pale", "thick"}));
            set_short("thick slice of yellow cheese");
            set_pshort("thick slices of yellow cheese");
            add_name("food");
            set_long("This is a thick slice of pale yellow cheese. It is "+
                "firm and ripe, with large holes in its interior.\n");
        }
