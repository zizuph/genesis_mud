


/*The Manor's Garden IV
 * Coded by Marisol (8/12/97)
 * The grasshopper npc are Gondor code. 
 *Copyright (c) Marisol Ramos 1997 */
/* Modified by Marisol(07/23/98) to be used in the village of
 * Ovejuno in Emerald.*/

#pragma strict_types

#include "defs.h"
inherit CASTLE_GARDEN;

void
create_emerald_garden()
{

    set_long("An old ruined garden lies in front of your eyes. "+
        "A tall hedge of rhododendrons surrounds the garden, making it "+
        "impossible to see outside the enclosure. This section is bereft "+
        "of roses, instead you find more exotic flowers from all over "+
        "the realm of Emerald. An explotion of oranges and reds "+
        "mingles with the green of the grass. The flowers are located "+
        "in both sides of the overgrown path that winds inside the "+        
        "garden. There are sounds of something walking in between the "+
        "plants.\n");


    add_item("plants",
        "Two different exotic plants from the realm of Emerald grow here. "+
        "Ones are bright orange and look like huge ears of wheat. The "+
        "others are orange-red and looks like open bird beaks.\n");

    add_item(({"orange plants", "orange flowers", "bright orange flowers", "bright orange plants"}),
        "This is an Orange Claw! This plant is usually found in "+
        "tropical jungles. The flowers look like dragon claws, so "+              
        "the reason for its name. Its leaves look like green lances.\n");

    add_item(({"orange-red plants", "orange-red flowers"}),
        "This is a Bird of Paradise! It is usually found deep in the "+
        "the jungle. The plant produces several flowers that look like "+
        "colorful orange-red bird beaks. This plant is extremely rare "+
        "and coveted by collectors.\n");

    add_exit("castle_garden06", "north");
    add_exit("castle_garden02", "south");

    reset_room();

}

void
reset_room()
{
    if(!present("grasshopper"));
    {
     setuid();
     seteuid(getuid());
     clone_object("/d/Gondor/common/npc/grasshopper")->move(this_object());
    }
}
