// path:         /d/Krynn/solamn/hctower/spur/obj/l_pasta.c         
// creator(s):   Grace  28 Sep 94
// last update:  
// desc:         a large plate of pasta      
// note:         food for the mess hall in the Knights' Spur
// bug(s):
// to-do:        add the props from the mentioned herbs to this food ?

inherit "/std/food";
#include "/sys/stdproperties.h"

        create_food()
        {
            set_amount(226);
            set_name("pasta");
            add_name(({"noodles", "plate"}));
            add_adj("large");   
            set_short("large plate of pasta");
            set_pshort("large plates of pasta");
            add_name("food");
            set_long("This is a large plate of pasta. The thin noodles have "+
                "been smothered with an aromatic tomato sauce. It smells "+
                "truly delicious and looks very nutritious.\n");
            add_item("noodles", "The noodles are thin and made from flour "+
                "and egg.\n"); 
            add_item(({"sauce","tomato sauce"}), "It is a red sauce made "+
                "of tomatoes and seasoned with herbs like basil, oregano, "+
                "garlic, and marjoram.\n");
            add_cmd_item(({"sauce","tomato sauce"}), "smell", "It smells "+
                "of herbs like basil, oregano, garlic, and marjoram.\n");
        }
