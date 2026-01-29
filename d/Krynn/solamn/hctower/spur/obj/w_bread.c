// path:         /d/Krynn/solamn/hctower/spur/obj/w_bread.c         
// creator(s):   Grace  28 Sep 94
// last update:  
// desc:         a loaf of whole wheat bread
// note:         food for the mess hall in the Knights' Spur
// bug(s):
// to-do:        

inherit "/std/food";
#include "/sys/stdproperties.h"

        create_food()
        {
            set_amount(120);
            set_name("bread");
            add_name(({"whole grain", "loaf"}));
            set_short("loaf of whole grain bread");
            set_pshort("loaves of whole-grain bread");
            add_name(({"food", "loaves"}));
            set_long("A loaf of whole grain bread kneaded by the head cook "+
                "of the Knights' Spur herself. Made of a tasty combination "+
                "of whole wheat and rye flours and just the right amount of "+
                "cornmeal, this bread is light and airy, with a hint of " +
                "molasses flavour. Caraway seeds are sprinkled on top.\n");
            add_item("seeds", "The seeds are from the caraway plant.\n"); 
        }

