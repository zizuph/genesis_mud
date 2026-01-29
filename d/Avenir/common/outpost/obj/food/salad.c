// file name:	~Avenir/common/outpost/obj/food/salad.c	
// creator(s): 	Lilith May 2022	
// purpose:	    Food for the Fort	
// revisions:     

inherit "/std/food.c";
#include <macros.h>
#include <composite.h>

public void
special_effect(int amnt)
{
    write("Your mouth waters with each tangy bite.\n");
}

void
create_food()
{
    set_name("salad");
    add_name("seaweed");
    set_adj("seaweed");
    set_short("seaweed salad");
    set_long("A mixed salad made of a variety of plants that "+
        "grow in the sea of Sybarus. This one has thin 'noodles' made "+
        "of laminaria kelp, reddish 'bacony' dulse, shredded jelly moss, "+
        "sea lettuce, sea mustard, and sea grapes tossed with "+
        "vinegar, some chopped shadow onion, and a spinkle of sesame seeds. "+
        "\n");
    set_amount(200);
	add_item(({"noodles", "laminaria", "kelp", "laminaria kelp", "dulse",
        "jelly moss", "sea lettuce", "sea mustard", "sea grapes"}),
        "It is an edible kind of seaweed.\n");
    add_item(({"shadow onion", "sesame seeds"}), "They have been "+
        "tossed in with a variety of sea weeds to add flavour to the "+
        "seaweed salad.\n");
    add_item(({"vinegar", "dressing"}), "Vingar has been mixed with sugar "+
        "to make a dressing for the seaweed salad.\n");
}

